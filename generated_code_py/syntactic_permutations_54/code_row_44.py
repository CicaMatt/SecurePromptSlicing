import flask 
from flask import Flask, request, render_template, send_file
app = Flask(__name__)

@app.route('/', methods=['GET'])
def login():
    return render_template("login.html")

@app.route('/', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    else:
        render_template("invalid_login.html")