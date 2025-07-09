
import re
from flask import Flask, render_template, request, redirect, url_for, flash
app = Flask(__name__)
app.secret_key='1234567890'
@app.route('/')
def index():
    return render_template('index.html')
    
@app.route('/login',methods=['POST','GET'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        cursor=mysql.connection.cursor()
        cursor.execute('select * from users where email=%s and password=%s',(email,password))
        user = cursor.fetchone()
        
    return render_template('login.html')
    
@app.route('/change',methods=['POST','GET'])
def change():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        cursor=mysql.connection.cursor()
        
        cursor.execute('select * from users where email=%s',(old_email,))
        user = cursor.fetchone()
        if user:
            if user['email'] == old_email and user['password'] == confirm_password:
                flash('Invalid Email or Password')
                return redirect(url_for('index'))
            else:
                cursor.execute('update users set email=%s where email=%s',(new_email,old_email))
                mysql.connection.commit()
                flash('Email changed successfully!')
        else:
            flash('No existing user with that email and password.')
        return redirect(url_for('index'))
    return render_template('change.html')
    
if __name__ == '__main__':
    app.run(debug=True)