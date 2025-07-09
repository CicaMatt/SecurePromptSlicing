import flask
from flask import request, redirect, render_template

app = flask.Flask(__name__)

@app.route('/')
def index():
  return 'Index Page'

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    # check if username and password are correct here
    if (check_user(username, password)):
      return render_template('secret.html', username=username)
    else:
        flask.flash('wrong username or password')
        return redirect('/login')

@app.route('/login')
def login():
  return 'You need to log in'

if __name__ == '__main__':
  app.run()