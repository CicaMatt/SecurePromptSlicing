import requests, json
from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    with open('users.json') as f:
        data = json.load(f)
        if username in data and data[username] == password:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))
@app.route('/home')
def home():
    return 'Home page'
if __name__ == '__main__':
    app.run()