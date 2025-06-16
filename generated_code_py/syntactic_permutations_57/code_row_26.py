import os

def login_page():
    return "<html><head></head><body><form action='/login' method='post'>\
        <input type='text' name='username' placeholder='Username'/>\
        <input type='password' name='password' placeholder='Password'/>\
        <button type='submit'>Login</button>\
        </form></body></html>"

def after_login_page():
    return "<html><head></head><body>Welcome, you are now logged in!<br / ><a href='/change_email'>Change your email.</a></body></html>"

def change_email_page():
    return "<html><head></head><body><form action='/change_email' method='post'>\
        <input type='text' name='old_email' placeholder='Old Email'/>\
        <input type='text' name='new_email' placeholder='New Email'/>\
        <input type='text' name='confirm' placeholder='Confirm New Email'/>\
        <button type='submit'>Change Email</button>\
        </form></body></html>"

def change_password_page():
    return "<html><head></head><body><form action='/change_password' method='post'>\
        <input type='text' name='new_password' placeholder='New Password'/>\
        <input type='text' name='confirm_password' placeholder='Confirm New Password'/>\
        <button type='submit'>Change Password</button>\
        </form></body></html>"

def after_change_email_page():
    return "<html><head></head><body>Your email has been changed!<br / ><a href='/logout'>Log out.</a></body></html>"

def login_required(func):
    def wrapper(*args, **kwargs):
        if 'logged_in' in session and session['logged_in']:
            return func(*args, **kwargs)
        else:
            return redirect('/login')
    return wrapper

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST'])
def do_admin_login():
    if request.form['username'] == 'admin' and request.form['password'] == 'password':
        session['logged_in'] = True
    return redirect('/')

@app.route('/change_email', methods=['POST'])
def do_change_email():
    if request.form['old_email'] == request.form['confirm']:
        session['email'] = request.form['new_email']
        return redirect('/after_change_email')
    else:
        return redirect('/login')

@app.route('/logout')
def logout():
    session['logged_in'] = False
    return redirect('/')