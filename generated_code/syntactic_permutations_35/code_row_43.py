from flask import Flask, render_template, request
import os

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def get_login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def post_login():
    username = request.form['username']
    password = request.form['password']
    
    with open('users.txt', 'r') as file:
        users = []
        for line in file:
            user, pwd = line.split(',')
            users.append(user)
            users.append(pwd)

    if username and password in users:
        return render_template('home.html', username=username)
    
    else:
        return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True, port=5000)