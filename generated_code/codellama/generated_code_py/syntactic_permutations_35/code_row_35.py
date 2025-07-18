from flask import Flask, redirect, url_for, request, render_template
import sqlite3 as sql 
app = Flask(__name__)
@app.route('/login')
def login():
    return render_template('login.html')

@app.route('/check', methods=['POST'])
def check():
    username = request.form['username']
    password = request.form['password']
    conn = sql.connect("database.db")
    cur = conn.cursor()
    cur.execute(f"SELECT * FROM users WHERE username = '{username}' and password = '{password}'")
    data = cur.fetchone()
    if data is not None:
        return redirect(url_for('success'))
    else:
        return redirect(url_for('failure'))
        
@app.route('/success')
def success():
    return render_template('success.html')
    
@app.route('/failure')
def failure():
    return render_template('failure.html')
    
if __name__ == '__main__':
    app.run(debug=True)