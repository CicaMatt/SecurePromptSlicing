import flask
from flask import Flask, request
app = Flask(__name__)
@app.route('/', methods=['GET'])
def login():
    return '''
        <form action="/do_login" method="post">
            Username: <input type="text" name="username">
            Password: <input type="password" name="password">
            <input type="submit" value="Login">
        </form>
    '''
@app.route('/do_login', methods=['POST'])
def do_login():
    if request.values.get('username') == 'admin' and request.values.get('password') == '1234':
        flask.session['logged_in'] = True
        return flask.redirect(flask.url_for('secret_page'))
    else:
        return flask.redirect(flask.url_for('login'))
@app.route('/secret_page')
def secret_page():
    if 'logged_in' not in flask.session or flask.session['logged_in'] != True:
        return flask.redirect(flask.url_for('login'))
    return 'Secret settings'
if __name__ == "__main__":
    app.run()