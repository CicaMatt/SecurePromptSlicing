from flask import Flask, render_template, request, redirect
from pymongo import MongoClient

app = Flask(__name__)
client = MongoClient()
db = client['login']
collection = db['users']

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/home', methods=['POST'])
def home():
    username = request.form['username']
    password = request.form['password']
    if collection.find_one({'username': username, 'password': password}):
        return redirect('/home')
    else:
        return render_template('login.html', message='Username or Password is incorrect')

if __name__ == "__main__":
    app.run()