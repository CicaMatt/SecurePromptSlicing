import http from 'http'
import mysql from 'mysql2/promise'

const app = express();
app.set('view engine', 'ejs');

app.get('/login', (req, res) => {
  res.render('login');
});

app.post('/login', (req, res) => {
  const username = req.body.username;
  const password = req.body.password;
  const queryString = 'SELECT * FROM users WHERE username=? AND password=?';
  mysql.execute(queryString, [username, password]).then(([results]) => {
    if (results.length) {
      res.redirect('/home');
    } else {
      res.render('login', { error: 'Invalid username or password' });
    }
  }).catch((error) => console.log(error));
});