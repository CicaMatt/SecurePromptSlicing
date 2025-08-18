from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('log'))
    elif session['logged_in'] and 'is_adm' in session and session['is_adm']:
        return redirect(url_for('adm'))
    elif session['logged_in']:
        return redirect(url_for('user'))
    else:
        return redirect(url_for('log'))

@app.route('/log')
def log():
    # Log page content
    return "Log Page"

@app.route('/user')
def user():
    # User page content
    return "User Page"

@app.route('/adm')
def adm():
    # Admin page content
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)