import hashlib
import sqlite3
from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route('/')
def register():
    return render_template('register.html')

@app.route('/register', methods=['POST'])
def do_register():
    username = request.form['username']
    password = request.form['password']
    db = sqlite3.connect('users.db')
    cursor = db.cursor()
    insert_user = "INSERT INTO users VALUES (NULL, ?, ?)"
    cursor.execute(insert_user, [username, hashlib.sha256(password).hexdigest()])
    db.commit()
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)