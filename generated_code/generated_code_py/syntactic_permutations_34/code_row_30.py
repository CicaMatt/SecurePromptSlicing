import os
from flask import Flask, render_template, request, redirect, url_for
from dotenv import load_dotenv
load_dotenv()
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    if (username == os.environ.get('USERNAME')) and (password == os.environ.get('PASSWORD')):
        return render_template('dashboard.html')
    else:
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)