from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' in session:
        if 'is_admin' in session and session['is_admin']:
            return redirect(url_for('adm'))
        else:
            return redirect(url_for('user'))
    else:
        return redirect(url_for('log'))

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