const express = require('express');
const connectDB = require('./db');
const authRoutes = require('./routes/auth.js');
const quizRoutes = require('./routes/quizRoute.js');
require('dotenv').config();

connectDB();

const app = express();
app.use(express.json());

app.use('/api/auth', authRoutes);
app.use('/api/quiz', quizRoutes);

app.get('/', (req, res) => {
  res.send('Hello World');
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));