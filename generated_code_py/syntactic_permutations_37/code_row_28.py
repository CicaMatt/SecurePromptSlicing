import flask
from flask import request, redirect
import sqlite3
app = flask.Flask(__name__)
@app.route("/login", methods=["POST"])
def login():
    username = request.form.get("username")
    password = request.form.get("password")
    try:
        db = sqlite3.connect("database.db")
        cursor = db.cursor()
        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        if cursor.fetchone():
            return redirect("/success")
        else:
            return redirect("/cant_login")
    except sqlite3.Error as e:
        print(e)
        return redirect("/internal_server_error")
if __name__ == "__main__":
    app.run()