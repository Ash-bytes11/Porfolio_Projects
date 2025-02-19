"""
AUTHORS: Jossie Batisso, AnhDuy Tran, and Aswanth Jeyaram Kumar
@HACKUMBC2024
"""

import os
from openai import OpenAI
from dotenv import load_dotenv
from fpdf import FPDF

load_dotenv()

def generate_quiz(topic, difficulty_level, num_questions):
    client = OpenAI(
        api_key=os.environ.get("OPENAI_API_KEY"),
    )

    prompt = (
        f"Create a quiz on the topic '{topic}' at the {difficulty_level} level with "
        f"{num_questions} questions. Each question should have multiple-choice answers "
        "with one correct answer and an answer key at the end."
    )

    # Call OpenAI API
    response = client.chat.completions.create(
        messages=[{"role": "user", "content": prompt}],
        model="gpt-3.5-turbo" 
    )

    # Extract the quiz
    quiz = response.choices[0].message.content
    return quiz

def save_questions_to_pdf(questions, pdf_filename="quiz_questions.pdf",topic = "Generated"):
    topic = topic.upper()
    pdf = FPDF()

    pdf.set_left_margin(20)
    pdf.set_right_margin(20)
    pdf.set_top_margin(20)

    pdf.add_page()

    # title font
    pdf.set_font('Arial', 'B', 16)
    pdf.cell(0, 10, f"{topic} QUIZ", ln=True, align='C')
    
    #New line
    pdf.ln(10)
    pdf.set_font('Arial', '', 12)

    # Write questions to PDF
    for question in questions:
        pdf.set_x(20)
        pdf.multi_cell(180, 10, question)

    pdf.output(pdf_filename)
    print(f"Quiz questions saved to {pdf_filename}")

def save_answers_to_pdf(answers, pdf_filename="quiz_answers.pdf"):
    # Initialize FPDF object
    pdf = FPDF()

    pdf.set_left_margin(20)
    pdf.set_right_margin(20)
    pdf.set_top_margin(20)

    pdf.add_page()

    pdf.set_font('Arial', 'B', 16)
    pdf.cell(0, 10, "Answer Key", ln=True, align='C')

    pdf.ln(10)
    pdf.set_font('Arial', '', 12)

    # Write answers to PDF
    for answer in answers:
        pdf.set_x(20)
        pdf.multi_cell(180, 10, answer)

    pdf.output(pdf_filename)
    print(f"Answer key saved to {pdf_filename}")

def main():
    topic = input("Enter the topic to test on: ")
    difficulty_level = input("Enter the level of difficulty (Expert, Intermediate, or Novice): ").lower()
    num_questions = int(input("Enter the number of questions: "))

    quiz = generate_quiz(topic, difficulty_level, num_questions)

    # Separate the questions and answers from the quiz text
    questions = []
    answers = []
    lines = quiz.split('\n')

    in_answer_section = False
    for line in lines:
        if line.lower().startswith('answer key:'):
            answers.append(line)
            in_answer_section = True
        elif not in_answer_section:
            questions.append(line)
        else:
            answers.append(line)

    save_questions_to_pdf(questions, "quiz_questions.pdf", topic)
    save_answers_to_pdf(answers, "quiz_answers.pdf")

if __name__ == "__main__":
    main()