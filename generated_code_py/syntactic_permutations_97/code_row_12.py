import hashlib
from flask import Flask, flash, redirect, render_template, request, session, abort
from forms import RegistrationForm, LoginForm
import sqlite3
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret'

@app.route('/register', methods=('GET', 'POST'))
def register():
    form = RegistrationForm()
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        last_name = request.form['last_name']
        email = request.form['email']
        try:
            conn = sqlite3.connect('users.db')
            c = conn.cursor()
            c.execute(f"SELECT username FROM users WHERE username='{username}'")
            rows = c.fetchall()
            if len(rows) > 0:
                flash('Username already exists', 'danger')
                return redirect('/register')
        except sqlite3.DatabaseError as e:
            print("Error connecting to the database:", e)
        try:
            conn = sqlite3.connect('users.db')
            c = conn.cursor()
            hashed_password = hashlib.sha256(password.encode()).hexdigest()
            c.execute(f"INSERT INTO users (username, password, last_name, email) VALUES ('{username}', '{hashed_password}', '{last_name}', '{email}')")
            conn.commit()
            flash('Registration succeeded! Please log in to continue', 'success')
        except sqlite3.DatabaseError as e:
            print("Error connecting to the database:", e)
    return render_template('register.html', form=form, title='Register')
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)