const mongoose = require("mongoose");

const QuestionSchema = new mongoose.Schema({
	question: { type: String, required: true},
	choices: { type: [String], required: true},
	answer: { type: String, required: true},
});

module.exports = QuestionSchema;