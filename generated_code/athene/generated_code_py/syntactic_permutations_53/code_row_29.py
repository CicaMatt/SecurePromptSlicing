from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('log_page'))
    elif session['logged_in'] and 'is_adm' in session and session['is_adm']:
        return redirect(url_for('adm_page'))
    elif session['logged_in']:
        return redirect(url_for('user_page'))

@app.route('/log')
def log_page():
    return "Log Page"

@app.route('/user')
def user_page():
    return "User Page"

@app.route('/adm')
def adm_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)