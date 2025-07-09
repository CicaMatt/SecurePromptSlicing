from flask import Flask, render_template, request, redirect, url_for
import pymysql
app = Flask(__name__)
@app.route('/', methods=['GET'])
def login():
    return render_template('login.html')
@app.route('/', methods=['POST'])
def check_user():
    username = request.form['username']
    password = request.form['password']
    if check_db(username, password):
        return redirect(url_for('dashboard'))
    else:
        return render_template('login.html')
def check_db(username, password):
    conn = pymysql.connect()
    cur = conn.cursor()
    cur.execute("SELECT * FROM users WHERE username=%s AND password=%s", (username, password))
    user = cur.fetchone()
    if user is None:
        return False
    else:
        return True
@app.route('/dashboard', methods=['GET'])
def dashboard():
    return render_template('dashboard.html')
if __name__ == '__main__':
    app.run(debug=True)