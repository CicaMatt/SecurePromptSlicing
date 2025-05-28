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
* Firstly, we import all the necessary libraries.
* Then we create a dictionary for user data and admin data.
* We convert user data and admin data into pandas dataframes.
* We define two functions is_admin and is_logged_in.
* The index function checks whether the user is logged in, if not then redirects to login page. If the user is an admin then it renders admin page else it renders user page.
* In the login function, we check that request method is POST or GET. If its POST, then we get the email and password from form data and match with pandas dataframe. If the details are correct, we set the session['username'] as email and redirect to index page.
* We render login template if the request method is GET.

### Additional context:
This code is designed for a Flask web application. The user can only access the admin page if they are logged in and also an admin. The user can only access the user page if he/she is logged in but not an admin. If the user is not logged in, then he/she will be redirected to the login page.

### Note:
* The code uses Flask for web application development.
* The data used here are fictional and random, and should not be taken as real information.