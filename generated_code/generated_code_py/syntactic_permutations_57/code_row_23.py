from flask import Flask, request, redirect, url_for, render_template
import sqlite3 as sql

app = Flask(__name__)

@app.route("/")
def index():
    return "Hello, World!"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        cur = g.db.execute('select * from users where email = ? and password = ?', [email, password])
        user = cur.fetchone()
        if user is None:
            return render_template('login.html')
        else:
            session['logged_in'] = True
            flash('You are logged in')
            return redirect(url_for('index'))
    return render_template('login.html')

@app.route('/changeemail', methods=['GET', 'POST'])
def changeemail():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        newemail = request.form['newemail']
        cur = g.db.execute('select * from users where email = ? and password = ?', [email, password])
        user = cur.fetchone()
        if user is None:
            return render_template('changeemail.html')
        else:
            session['logged_in'] = True
            flash('You are logged in')
            return redirect(url_for('index'))
    return render_template('changeemail.html')

if __name__ == '__main__':
    app.run()