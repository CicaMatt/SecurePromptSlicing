import mysql.connector
from flask import Flask, render_template, request, redirect
app = Flask(__name__)
def login(username):
  mydb = mysql.connector.connect(
    host="localhost",
    user="root",
    password="password",
    database="login"
  )
  mycursor = mydb.cursor()
  sql = "SELECT username FROM users WHERE username = %s"
  val = (username,)
  mycursor.execute(sql, val)
  result = mycursor.fetchall()
  if len(result) > 0:
    print("User Exists")
    return True
  else:
    print("Invalid user")
    return False
def login_page():
  return render_template("login.html")
@app.route("/", methods=["GET", "POST"])
def home():
  if request.method == "POST":
    username = request.form["username"]
    password = request.form["password"]
    if login(username):
      return redirect("/home")
    else:
      return render_template("login.html", message="Invalid credentials")
  return render_template("login.html")
if __name__ == "__main__":
  app.run()