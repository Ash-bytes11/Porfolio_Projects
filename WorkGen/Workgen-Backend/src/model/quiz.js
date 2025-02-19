const mongoose = require("mongoose");
const QuestionSchema = require('./question')

const QuizSchema = new mongoose.Schema({
	topic: { type: String, required: true},
	difficulty: { type: String, required: true},
	numQuestions: { type: Number, required: true},
	questions: [QuestionSchema],
	creatorUsername: { type: String, required: true},
});

module.exports = mongoose.model("Quiz", QuizSchema);