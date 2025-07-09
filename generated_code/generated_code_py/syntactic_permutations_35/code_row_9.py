from flask import Flask, render_template, request, redirect
import sqlite3 as sql
app = Flask(__name__)
return render_template("login.html")
username = request.form["username"]
password = request.form["password"]
conn = sql.connect('database.db')
cursor = conn.cursor()
cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
result = cursor.fetchall()
return redirect('/home')
return redirect('/login')
return "Home page"
app.run(debug=True)