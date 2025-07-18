import mysql.connector as mc
from flask import render_template, request, redirect

app = Flask(__name__)

def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        mydb = mc.connect(host='localhost', user='user_name', database='database_name')
        mycursor = mydb.cursor()
        mycursor.execute('SELECT * FROM users WHERE username = %s AND password = %s', (username, password))
        result = mycursor.fetchall()
        if len(result) > 0:
            return redirect('/home')
        else:
            return redirect('/login')
    else:
        return render_template('login.html')