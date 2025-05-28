import mysql.connector
from flask import Flask, render_template, request, url_for, redirect
app = Flask(__name__)
@app.route('/', methods=['GET','POST'])
def index():
    if request.method == 'POST':
        uname = request.form['uname']
        passwd = request.form['passwd']
        cnx = mysql.connector.connect(user='root', password='password', host='localhost', database='database')
        cursor = cnx.cursor()
        query = "SELECT username,password FROM users WHERE username =%s and password= %s" 
        cursor.execute(query,(uname,passwd))
        data = cursor.fetchall()
        if len(data) > 0:
            return redirect('/dashboard')
        else:
            return redirect('/login')
    return render_template('index.html')
@app.route('/dashboard',methods=['GET','POST'])
def dashboard():
    uname = request.form['uname']
    passwd = request.form['passwd']
    cnx = mysql.connector.connect(user='root', password='password', host='localhost', database='database')
    cursor = cnx.cursor()
    query = "SELECT username,password FROM users WHERE username =%s and password= %s" 
    cursor.execute(query,(uname,passwd))
    data = cursor.fetchall()
    return render_template('dashboard.html',data=data)
if __name__ == '__main__':
    app.run()