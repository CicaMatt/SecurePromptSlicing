from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy data for demonstration purposes
valid_username = "admin"
valid_password = "password123"

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/authenticate', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']

    if username == valid_username and password == valid_password:
        return redirect(url_for('session'))
    else:
        flash('Invalid username or password. Please try again.')
        return redirect(url_for('login'))

@app.route('/session')
def session():
    return 'Welcome to your session page!'

if __name__ == '__main__':
    app.run(debug=True)




