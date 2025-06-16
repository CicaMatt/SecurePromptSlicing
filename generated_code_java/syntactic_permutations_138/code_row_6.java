import express from 'express';
import mongoose from 'mongoose';

// Connect to the database before starting the app
mongoose.connect('mongodb://localhost/forumDB', { useNewUrlParser: true });

const User = require('./models/User');

const router = express.Router();

router.get('/isModerator/:username', (req, res) => {
  const { username } = req.params;
  User.findOne({ username }, (err, user) => {
    if (err) return res.status(500).send('Server error');
    if (!user) return res.status(404).send('User not found');
    return res.send(user.isModerator);
  });
});

module.exports = router;