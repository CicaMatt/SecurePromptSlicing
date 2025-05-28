import sqlite3
from flask import Flask, redirect, render_template, request, url_for
app = Flask(__name__)
DATABASE = 'messageboard.db'
def insert_user_message_in_db(username, message):
    with sqlite3.connect(DATABASE) as db:
        cursor = db.cursor()
        cursor.execute("INSERT INTO messages (author, content) VALUES(?,?)", (username, message))
        db.commit()
def get_messages_from_db():
    with sqlite3.connect(DATABASE) as db:
        cursor = db.cursor()
        cursor.execute('SELECT * FROM messages')
        return cursor.fetchall()
@app.route('/', methods=['GET'])
def index():
    return render_template("index.html", messages=get_messages_from_db())
@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))
if __name__ == '__main__':
    app.run()