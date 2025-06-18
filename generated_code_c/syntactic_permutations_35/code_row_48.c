import { login } from '../auth';
const express = require('express');
const router = express.Router();
const db = require('./database')
router.get('/', function (req, res) {
  res.sendFile(path.join(__dirname + './login.html'));
});
router.post('/', function (req, res) {
  const username = req.body.username;
  const password = req.body.password;
  login(username, password).then((result) => {
    if (result === true) {
      res.redirect('../home');
    } else {
      res.sendFile(path.join(__dirname + './login.html'));
    }
  });
});
module.exports = router;