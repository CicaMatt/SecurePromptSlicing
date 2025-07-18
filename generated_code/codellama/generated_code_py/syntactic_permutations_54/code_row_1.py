from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route("/login", methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    if username == 'admin' and password == 'password':
        return redirect(url_for('admin_page'))
    else:
        return "You are not an admin!"