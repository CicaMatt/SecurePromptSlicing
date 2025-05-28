import os
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        # check the database for the username and password combination
        # if it does not exist, then redirect to the login page
        return render_template('login.html')
    else:
        return render_template('home.html')

if __name__ == '__main__':
    app.run(debug=True)