from flask import Flask, render_template, url_for, request, redirect
import sqlite3
app = Flask(__name__)
app.config['DEBUG'] = True

def insert_user_message_in_db(username, message):
    with sqlite3.connect('database.db') as conn:
        c = conn.cursor()
        c.execute("INSERT INTO messages VALUES (:username, :message)", {
                  'username': username, 'message': message})
        conn.commit()

@app.route('/', methods=['GET'])
def get():
    with sqlite3.connect('database.db') as conn:
        c = conn.cursor()
        c.execute("SELECT * FROM messages")
        messages = c.fetchall()
        return render_template('index.html', messages=messages)

@app.route('/', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('get'))

if __name__ == '__main__':
    app.run()