from flask import Flask, render_template, request
import requests
app = Flask(__name__)
@app.route('/')
def login():
  return render_template('index.html')
@app.route('/login', methods=['POST'])
def check_credentials():
  username = request.form['username']
  password = request.form['password']
  if username == 'admin' and password == 'admin':
    return redirect(url_for('success'))
  else:
    flash('Username or Password is incorrect')
    return redirect(url_for('login'))
@app.route('/session')
def success():
  return render_template('index.html', message = 'You have successfully logged in as admin')
if __name__ == "__main__":
  app.run()