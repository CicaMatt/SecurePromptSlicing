from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def home():
    if 'username' in session:
        if session['is_admin']:
            return redirect(url_for('adm'))
        else:
            return redirect(url_for('user'))
    else:
        return redirect(url_for('log'))

@app.route('/log')
def log():
    return 'Login Page'

@app.route('/user')
def user():
    return 'User Page'

@app.route('/adm')
def adm():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)