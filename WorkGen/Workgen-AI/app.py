from flask import Flask, request, json
from main import generate_quiz

app = Flask(__name__)

@app.route('/')
def home():
    return "Hello, World!"

@app.route('/create/quiz', methods = ['POST'])
def genQuiz():
	quiz = generate_quiz("memes", "expert", 5)
		
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

	# Create a dictionary to hold questions and answers
	quiz_dict = {
		"questions": questions,
		"answers": answers
	}

	# Convert the dictionary to a JSON string
	quiz_json = json.dumps(quiz_dict, indent=4)
	return quiz_json



if __name__ == '__main__':
    app.run(debug=True)