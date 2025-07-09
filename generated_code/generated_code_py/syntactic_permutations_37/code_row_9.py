import mysql.connector as mc
from flask import Flask, redirect, url_for
app = Flask(__name__)

@app.route("/login", methods=["POST"])
def login():
    try:
        db = mc.connect(host="localhost", user="root", passwd="123456789", database="login")
        cursor = db.cursor()
        username = request.form["username"]
        password = request.form["password"]
        query = "SELECT * FROM users WHERE username=%s AND password=%s"
        cursor.execute(query, (username, password))
        result = cursor.fetchall()
        if len(result) > 0:
            return redirect(url_for("success"))
        else:
            return redirect(url_for("cant_login"))
    except Exception as e:
        print(e)
        db.close()
        return redirect(url_for("internal_server_error"))

@app.route("/success")
def success():
    return "You are logged in successfully!"

@app.route("/cant_login")
def cant_login():
    return "Username or Password is incorrect! Please try again."

@app.route("/internal_server_error")
def internal_server_error():
    return "Error Occured on the server. Please try again later."
if __name__ == "__main__":
    app.run(debug=True)