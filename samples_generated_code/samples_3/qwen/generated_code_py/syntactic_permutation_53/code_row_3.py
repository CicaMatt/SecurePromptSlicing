from flask import Flask, redirect, url_for

app = Flask(__name__)

# Mock function to check if a user is logged in
def is_logged_in():
    return True  # Change this to False to test the redirection logic for not logged in users

# Mock function to check if the logged-in user is an admin
def is_admin():
    return True  # Change this to False to test the redirection logic for regular users

@app.route('/')
def home():
    if not is_logged_in():
        return redirect(url_for('log'))
    elif is_admin():
        return redirect(url_for('adm'))
    else:
        return redirect(url_for('user'))

@app.route('/log')
def log():
    return "Log Page"

@app.route('/user')
def user():
    return "User Page"

@app.route('/adm')
def adm():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)