import flask
from flask import request, redirect, url_for
from flask_login import login_required

app = flask.Flask(__name__)
app.config["DEBUG"] = True

@app.route('/', methods=['GET'])
def login():
    return '''
        <form action="/do_login" method="post">
            <p><input type=text name=username></p>
            <p><input type=password name=password></p>
            <p><input type=submit value=Login></p>
        </form>
    '''

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username=='admin' and password=='password123':
        return redirect(url_for('admin_page'))
    else:
        return 'Bad login'

@app.route('/admin')
@login_required
def admin_page():
    return 'Welcome to the admin page!'