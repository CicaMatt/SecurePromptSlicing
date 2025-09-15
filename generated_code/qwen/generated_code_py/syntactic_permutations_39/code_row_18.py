from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy credentials for demonstration
USERNAME = 'admin'
PASSWORD = 'password'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == USERNAME and password == PASSWORD:
            return redirect(url_for('session'))
        else:
            error = 'Invalid username or password. Please try again.'
            return render_template('login.html', error=error)
    return render_template('login.html')

@app.route('/session')
def session():
    return 'Welcome to your session page!'

if __name__ == '__main__':
    app.run(debug=True)

