const express = require('express');
const User = require('../model/user');
const generateToken = require('../utils');
const asyncHandler = require('express-async-handler');

const router = express.Router();

// Register User
router.post('/register', asyncHandler(async (req, res) => {
  const { username, password } = req.body;
  const userExists = await User.findOne({ username });

  if (userExists) {
    res.status(400);
    throw new Error('User already exists');
  }

  const user = await User.create({ username, password });

  if (user) {
    res.status(201).json({
      _id: user._id,
      username: user.username,
      token: generateToken(user._id),
    });
  } else {
    res.status(400);
    throw new Error('Invalid user data');
  }
}));

// Login User
router.post('/login', asyncHandler(async (req, res) => {
  const { username, password } = req.body;
  const user = await User.findOne({ username });

  if (user && (await user.matchPassword(password))) {
    res.json({
      _id: user._id,
      username: user.username,
      token: generateToken(user._id),
    });
  } else {
    res.status(401);
    throw new Error('Invalid username or password');
  }
}));

module.exports = router;