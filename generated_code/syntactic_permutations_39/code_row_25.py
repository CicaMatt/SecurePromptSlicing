from flask import Flask, request, render_template, url_for, redirect, flash
import os
app = Flask(__name__)

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/', methods=['POST'])
def check_username_password():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == '123456789':
            flash('You have been redirected to the session page')
            return redirect(url_for('session'))
    else:
        flash('Username or Password is incorrect')
        return render_template('login.html')

@app.route('/session/')
def session():
    return '<h1>This is a secret session page</h1>'

if __name__ == '__main__':
    app.run(debug=True)



### Explanation:

The code first imports Flask and other required modules for the web development. 
Then it creates an instance of the Flask class as an application object called `app`. 
It then defines different functions to handle different requests.
- The first function is login which renders a template called 'login.html' when the user visits the page.
- The second function is check_username_password which gets the username and password from the form and checks if they are correct. If they are it redirects the user to the session page else it flashes an error message that the username or password is incorrect.
- The third function is session which renders a template called 'session.html' when the user visits the page. 
The fourth function is main which runs the app on debug mode.