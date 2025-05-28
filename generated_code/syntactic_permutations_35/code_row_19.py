import os
import re
from flask import Flask, request, render_template

app = Flask(__name__)
app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if check_login(username, password):
            return render_template('home.html')
        else:
            flash('Incorrect credentials!')
            return redirect(url_for('login'))
    return render_template('login.html')

def check_login(username, password):
    with open('users.txt', 'r') as file:
        if f'{username}:{password}' in file.read():
            return True
        else:
            return False