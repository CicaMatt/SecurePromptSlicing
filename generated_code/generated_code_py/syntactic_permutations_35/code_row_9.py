3
import mysql.connector as mc
from flask import Flask, render_template, request, flash, redirect, url_for, session

app = Flask(__name__)
app.secret_key = "my secret key"

def login(username, password):
    try:
        cnx = mysql.connector.connect(user='root', password='password', host='localhost', database='db1')
        cursor = cnx.cursor()
        query = ("SELECT * FROM user_table WHERE username=%s AND password=%s")
        cursor.execute(query, (username, password))
        data = cursor.fetchall()
        if len(data) > 0:
            flash("Login successful!", "success")
            return redirect(url_for('home'))
        else:
            flash("Invalid username or password", "danger")
            return redirect(url_for('login'))
    except mysql.connector.Error as err:
        print(err)

@app.route("/login", methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        login(username, password)
    return render_template("login.html")

@app.route("/home")
def home():
    return "Home Page"

if __name__ == "__main__":
    app.run()