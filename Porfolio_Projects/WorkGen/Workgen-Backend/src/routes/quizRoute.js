const express = require('express');
const Quiz = require('../model/quiz');
const asyncHandler = require('express-async-handler');

const router = express.Router();

// Create Quiz in DB
router.post('/create', asyncHandler(async (req, res) => {
	const { topic, difficulty, numQuestions, questions, creatorUsername } = req.body;
  
	const quiz = await Quiz.create({ topic, difficulty, numQuestions, questions, creatorUsername });
  
	if (quiz) {
	  res.status(201).json({
		id: quiz.id,
		topic: quiz.topic,
		difficulty: quiz.difficulty,
		numQuestions: quiz.numQuestions,
		questions: quiz.questions,
		creatorUsername: quiz.creatorUsername
	  });
	} else {
	  res.status(400);
	  throw new Error('Invalid user data');
	}
}));

// Retrieve Quizzes using creatorUsername
router.get('/creator/:creatorName', asyncHandler(async (req, res) => {
	
	const creatorName = req.params.creatorName;
	const quizzes = await Quiz.find({ 'quizzes.creatorUsername': creatorName});

	if(quizzes){
		res.json(quizzes);
	}else{
		res.status(500).json({message: "Creator Username not found"})
	}
}));

// Retrive Quiz using id
router.get('/:id', asyncHandler(async (req, res) => {

	const quizId = req.params.id;
	const quiz = await Quiz.findById(quizId);

	if(quiz){
		res.json(quiz);
	}else{
		res.status(500).json({message: "Quiz not found"})
	}
}))

// Delete Quiz using id
router.delete('/delete/:id', asyncHandler(async (req, res) => {

	const quizId = req.params.id;
	try{
		const quiz = await Quiz.findByIdAndDelete(quizId);

		if(!quiz){
			return res.status.json({message: "Quiz not found"});
		}
		res.json({message: "Quiz deleted"});
	} catch(err){
		res.status(500).json({message: err.message});
	}
}));

module.exports = router;