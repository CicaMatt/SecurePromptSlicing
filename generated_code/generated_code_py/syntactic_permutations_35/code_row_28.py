import os
from flask import Flask, request, url_for, render_template, session
app = Flask(__name__)

@app.route('/')
def home():
    return render_template('home.html')

@app.route('/login', methods=['POST'])
def login():
    form = request.form
    username = form['username']
    password = form['password']
    with open(os.path.join(app.root_path, 'users.csv'), 'r') as f:
        users = [line.split(',') for line in f]
        if (username, password) in users:
            session['logged_in'] = True
    return render_template('login.html', form=form)

@app.route('/logout')
def logout():
    session['logged_in'] = False
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)