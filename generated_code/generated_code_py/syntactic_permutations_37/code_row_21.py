import os
from flask import Flask, jsonify, request, redirect, render_template

app = Flask(__name__)

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def do_admin_login():
    try:
        username, password = request.form['username'], request.form['password']
        if check_login(username, password):
            return redirect('/success')
        else:
            return redirect('/cant_login')
    except:
        return redirect('/internal_server_error')

def check_login(username, password):
    # Code to query a database and check if the username and password are correct.
    # Returns True or False based on the result of the query.
    pass

if __name__ == '__main__':
    app.run()