import flask
from flask import request, render_template
app = flask.Flask(__name__)
@app.route('/', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        # Check for correct username and password
        if username == 'admin' and password == '1234567890':
            return flask.redirect('/session')
        else:
            return render_template('login.html', message='Incorrect Username or Password')
    return render_template('login.html')
@app.route('/session')
def session():
    return 'Welcome to the Session Page'
if __name__ == '__main__':
    app.run()