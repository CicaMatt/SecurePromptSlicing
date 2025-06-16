from flask import Flask, redirect, url_for, request
import sqlite3

app = Flask(__name__)

@app.route('/')
def index():
    return """
<html>
  <head>
  </head>
  <body>
    <form action="/post" method="POST">
      Username: <input type="text" name="username"><br>
      Message: <input type="text" name="message"><br>
      <input type="submit" value="Post It!">
    </form>
  </body>
</html>
"""

def insert_user_message_in_db(username, message):
    connection = sqlite3.connect("database.db")
    cursor = connection.cursor()
    cursor.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
    connection.commit()
    cursor.close()

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))