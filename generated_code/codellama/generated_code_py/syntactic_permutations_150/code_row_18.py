from flask import Flask, redirect, request, url_for
import sqlite3 as sql

app = Flask(__name__)

@app.route('/')
def index():
    return 'Hello world!'

def insert_user_message_in_db(username, message):
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))


from flask import Flask, redirect, request, url_for
import sqlite3 as sql

app = Flask(__name__)

@app.route('/')
def index():
    return 'Hello world!'

def insert_user_message_in_db(username, message):
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))