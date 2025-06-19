// File uploader UI using NodeJS and Express
const express = require('express');
const multer  = require('multer'); // middleware for handling multipart/form-data
const upload = multer({ dest: 'uploads/' });

const app = express();

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
});

// Single file upload with name "file"
app.post('/single-file/', upload.single('file'), function (req, res) {
  const file = req.file;
  console.log(file);

  if (!file) {
    const error = new Error('Please upload a file');
    error.httpStatusCode = 400;
    return next(error);
  }

  res.send('File uploaded!');
});

// Multiple files upload with name "files"
app.post('/multiple-files/', upload.array('files'), function (req, res) {
  const files = req.files;
  console.log(files);

  if (!files) {
    const error = new Error('Please upload at least one file');
    error.httpStatusCode = 400;
    return next(error);
  }

  res.send('Files uploaded!');
});

app.listen(3000, function () {
  console.log('Server started on port 3000');
});