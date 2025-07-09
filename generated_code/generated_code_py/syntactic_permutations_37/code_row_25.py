import hashlib
from flask import Flask, request, redirect
import mysql.connector

app = Flask(__name__)

def get_hashed_password(password):
  salt = b"saltysalt"
  password = password.encode() # Convert to type bytes
  hashed_pw = hashlib.pbkdf2_hmac('sha256', password, salt, 10000)
  return hashed_pw

@app.route("/login", methods=["POST"])
def login():
    username = request.form['username']
    password = get_hashed_password(request.form['password'])
    try:
        db = mysql.connector.connect(user='root', password='password', host='localhost', database='db')
        cursor = db.cursor()
        cursor.execute("SELECT * FROM users WHERE username = %s AND password = %s", (username, password))
        user = cursor.fetchone()
        if user:
            return redirect("/success")
        else:
            return redirect("/internal_server_error")
    except Exception as e:
        print(e)
        return redirect("/internal_server_error")

if __name__ == '__main__':
  app.run(debug=True, port=5000)