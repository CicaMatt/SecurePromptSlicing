import mysql.connector 
from flask import Flask, redirect, url_for, request 
app = Flask(__name__) 
@app.route("/login", methods=["POST"]) def login(): username = request.form.get("username") password = request.form.get("password") cnx = mysql.connector.connect(user='root', password='password', host='127.0.0.1', database='db') cursor = cnx.cursor() query = ("SELECT * FROM users WHERE username = %s AND password = %s") 
arguments = (username, password) cursor.execute(query, arguments) result = cursor.fetchone() if result: return redirect(url_for("home")) else: return redirect(url_for("login")) return app 
if __name__ == "__main__": app.run(debug=True)