from flask import Flask, request, render_template
app = Flask(__name__)
app.config['DEBUG'] = True
@app.route('/', methods=['GET','POST'])
def login():
    error = None
    if request.method == 'POST':
        if valid_login(request.form['username'], request.form['password']):
            return log_the_user_in(request.form['username'])
        else:
            error = 'Invalid username/password'
    # the code below is executed if the request method was GET or the login was invalid
    return render_template('login.html', error=error)
@app.route('/change_email', methods=['GET','POST'])
def change_email():
    error = None
    if request.method == 'POST':
        if valid_confirmation(request.form['old_email'], request.form['new_email'], request.form['password']):
            return render_template('change_email.html', new_email=request.form['new_email'])
        else:
            error = 'Invalid old email, new email or password'
    # the code below is executed if the request method was GET or the login was invalid
    return render_template('change_email.html', error=error)
def valid_login(username, password):
    # this function checks the username and password against a database table
    # for simplicity sake we'll just compare to a hardcoded string
    return username == 'admin' and password == 'password'
def log_the_user_in(username):
    # this function logs the user in, which in our case is simply storing the username
    # in the session variable
    session['logged_in'] = True
    session['username'] = username
    return render_template('login.html', success='You are now logged in')
def valid_confirmation(old_email, new_email, password):
    # this function checks the old email, new email and confirm password against a database table
    # for simplicity sake we'll just compare to hardcoded strings
    return old_email == 'admin@example.com' and new_email == 'new_email@example.com' and password == 'password'
if __name__ == '__main__':
    app.run()