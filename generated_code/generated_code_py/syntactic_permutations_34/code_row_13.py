import os 
from flask import Flask, render_template, request, session
app = Flask(__name__)
app.secret_key = "abcd"
@app.route("/")
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST', 'GET'])
def login():
    if request.method == 'POST':
        user = request.form['username']
        password = request.form['password']
        if user == "admin" and password == "12345678":
            return redirect(url_for('dashboard'))
        else:
            return render_template('index.html', message="Invalid credentials")
    else:
        session.pop('logged_in')
        return render_template('index.html')

@app.route('/dashboard')
def dashboard():
    if 'logged_in' in session:
        return "Welcome %s!" % session['username']
    return redirect(url_for('login'))
if __name__ == "__main__":
    app.run()