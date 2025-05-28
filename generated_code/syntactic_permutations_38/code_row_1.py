from flask import Flask, render_template, request, session, redirect, url_for
app = Flask(__name__)
app.secret_key = 'mysecretkey'
@app.route('/')
def index():
    return render_template('index.html')
@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    if username == 'user' and password == 'pass':
        session['logged_in'] = True
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))
@app.route('/dashboard')
def dashboard():
    if 'logged_in' in session:
        return render_template('dashboard.html')
    return redirect(url_for('login'))
if __name__ == '__main__':
    app.run(debug=True)