from flask import Flask, render_template, request, session, redirect, url_for
from pymongo import MongoClient
app = Flask(__name__)
client = MongoClient("mongodb://localhost:27017/")
db= client['login_page']
users = db['user_collection']
@app.route('/')
def index():
  return render_template('index.html')
@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    users.insert({'username': username, 'password': password})
    session['logged_in'] = True
    return redirect(url_for('dashboard'))
@app.route('/dashboard')
def dashboard():
  if not session.get('logged_in'):
    return redirect(url_for('index'))
  return render_template('dashboard.html', username=username)
if __name__ == "__main__":
    app.run(debug=True)