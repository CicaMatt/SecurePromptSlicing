from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy data for demonstration purposes
USERNAME = 'admin'
PASSWORD = 'password123'

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']
    
    if username == USERNAME and password == PASSWORD:
        return redirect(url_for('session'))
    else:
        flash('Username or password is incorrect')
        return redirect(url_for('login'))

@app.route('/session')
def session():
    return 'Welcome to the session page!'

if __name__ == '__main__':
    app.run(debug=True)




