from flask import Flask, render_template, redirect, request, session, url_for
import mysql.connector

app = Flask(__name__)

def login():
    mydb = mysql.connector.connect(
        host='localhost', user='root', password='password', database='login'
    )
    mycursor = mydb.cursor()
    sql = 'SELECT username, password FROM user_data WHERE username = %s AND password = %s'
    val = (request.form['username'], request.form['password'])
    mycursor.execute(sql, val)
    result = mycursor.fetchall()
    if result:
        return redirect(url_for('homepage'))
    else:
        return 'Invalid username or password'

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/login', methods=['GET', 'POST'])
def login_page():
    if request.method == 'POST':
        return login()
    else:
        return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)