import mysql.connector as sql
from flask import Flask, render_template, request, session, redirect, url_for

app = Flask(__name__)
app.config['SECRET_KEY'] = 'yoursecretkey'

def connect_to_db():
    return sql.connect(host='localhost', user='username', password='password', db='database')

@app.route("/", methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        cursor = connect_to_db().cursor()
        query = ("SELECT * FROM users WHERE username = %s AND password = %s")
        cursor.execute(query, (username, password))
        user = cursor.fetchone()
         if user:
            return redirect(url_for('protected'))
        else:
            return render_template("login.html", message="Invalid Credentials!")
    return render_template("login.html")

@app.route("/protected")
def protected():
    username = session['username']
    cursor = connect_to_db().cursor()
    query = ("SELECT * FROM users WHERE username = %s")
    cursor.execute(query, (username,))
    user = cursor.fetchone()
    if user:
        return render_template("protected.html", username=username)
    else:
        return redirect(url_for('login'))

@app.route("/logout")
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == "__main__":
    app.run()