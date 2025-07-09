import sqlite3
import flask
import os
from flask import Flask, request, session, redirect, url_for
app = Flask(__name__)
app.secret_key = 'secret key'
@app.route('/')
def main_page():
    return '''<form action="/post" method="post">
                <input name="message"></input>
                <button type="submit">Post</button>
            </form>'''

@app.route('/post', methods=['POST'])
def post():
    message = request.form['message']
    insert_user_message_in_db(message)
    return redirect(url_for('main_page'))

def insert_user_message_in_db(message):
    db = get_db()
    db.execute("INSERT INTO messages (message) VALUES (?)", [message])
    db.commit()