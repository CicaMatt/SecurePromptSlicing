from flask import Flask, render_template, request, url_for, redirect, session
import pandas as pd 
import numpy as np

app = Flask(__name__)
app.secret_key = "password"

user_data = {'email': ['user1@example.com', 'user2@example.com'],
             'password': ['pass1', 'pass2']}

admin_data = {'email': ['admin1@example.com', 'admin2@example.com'],
              'password': ['pass3', 'pass4']}

user_df = pd.DataFrame(user_data)
admin_df = pd.DataFrame(admin_data)

def is_admin(email):
    return admin_df['email'].str.contains(email).any()

def is_logged_in():
    if 'username' in session:
        return True
    else:
        return False

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    elif is_admin(session['username']):
        return render_template("admin.html")
    else:
        return render_template("user.html")

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == "POST":
        email = request.form.get('email')
        password = request.form.get('password')
        if user_df[user_df['email']==email]['password'].values[0] == password:
            session['username'] = email
            return redirect(url_for('index'))
    else:
        return render_template("login.html")

### Explanation








### Additional context:


### Note:

