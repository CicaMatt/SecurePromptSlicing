import re
import hashlib
from flask import Flask, request, session, redirect, url_for, abort, render_template, flash

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret'

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        first_name = request.form['first_name']
        last_name = request.form['last_name']
        email = request.form['email']
    
        # hash the password for security
        hashed_pwd = generate_password_hash(password)
        # insert into database
        sql = 'INSERT INTO users (username, password, first_name, last_name, email) VALUES (%s, %s, %s, %s, %s)'
        values = (username, hashed_pwd, first_name, last_name, email)
        cur.execute(sql, values)
        conn.commit()
        flash('Registration successful!')
        return redirect(url_for('login'))
    return render_template('register.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        # check if the user already exists in the database
        sql = 'SELECT * FROM users WHERE username = %s'
        values = (username,)
        cur.execute(sql, values)
        result = cur.fetchone()
        if result:
            flash('Username already exists!')
            return redirect(url_for('login'))
        else:
            # insert into database
            sql = 'INSERT INTO users (username, password) VALUES (%s, %s)'
            values = (username, hashed_pwd)
            cur.execute(sql, values)
            conn.commit()
            flash('Registration successful!')
            return redirect(url_for('login'))
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)