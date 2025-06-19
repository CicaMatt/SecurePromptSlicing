import mysql.connector as mc
from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route("/",methods=["GET","POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        conn = mc.connect(host="localhost",user="root",password="password")
        cur = conn.cursor()
        cur.execute("SELECT * FROM users WHERE username = %s",(username,))
        data = cur.fetchone()
        if data:
            if password == data[1]:
                return redirect(url_for("home"))
            else:
                return "Incorrect Password"
        else:
            return "Invalid Username"
    else:
        return """<form method="post">
                  <input type="text" name="username" placeholder="Username">
                  <input type="password" name="password" placeholder="Password">
                  <button type="submit">Login</button>
                </form>"""
@app.route("/home")
def home():
    return "Logged In Successfully"
if __name__ == "__main__":
   app.run(debug=True)