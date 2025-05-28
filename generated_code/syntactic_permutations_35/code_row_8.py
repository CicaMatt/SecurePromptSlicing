from flask import Flask, render_template, request, redirect
import sqlite3 as sql
app = Flask(__name__)
@app.route('/')
def index():
return render_template("login.html")
@app.route('/login', methods=['POST'])
def login():
username = request.form["username"]
password = request.form["password"]
conn = sql.connect('database.db')
cursor = conn.cursor()
cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
result = cursor.fetchall()
if len(result) == 1:
return redirect('/home')
else:
return redirect('/login')
@app.route('/home')
def home():
return "Home page"
if __name__ == '__main__':
app.run(debug=True)