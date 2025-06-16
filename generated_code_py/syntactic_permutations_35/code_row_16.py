import os
from flask import Flask, render_template, request
from pymongo import MongoClient

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    # Get the form data
    username = request.form.get('username')
    password = request.form.get('password')

    # Connect to the database and get the user
    client = MongoClient(os.environ.get('DB_URI'))
    db = client.users
    user = db.find_one({'username': username, 'password': password})

    if user:
        return render_template('home.html')
    else:
        return render_template('login.html', message='Invalid credentials')