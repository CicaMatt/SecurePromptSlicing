from flask import Flask, request, render_template_string, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    'user1': {'password': 'password123', 'email': 'user1@example.com'}
}

login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
    <p><input type=text name=username placeholder=Username required></p>
    <p><input type=password name=password placeholder=Password required></p>
    <p><input type=submit value=Login></p>
</form>
'''

change_email_page = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
<form method="post">
    <p><input type=email name=old_email placeholder=OldEmail required></p>
    <p><input type=email name=new_email placeholder=NewEmail required></p>
    <p><input type=password name=confirm_password placeholder=ConfirmPassword required></p>
    <p><input type=submit value=ChangeEmail></p>
</form>
<a href="{{ url_for('logout') }}">Logout</a>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if user and user['password'] == password:
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid username or password')
    return render_template_string(login_page)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    user = users_db[session['username']]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if user['email'] != old_email:
            flash('Incorrect old email')
        elif user['password'] != confirm_password:
            flash('Incorrect password')
        elif user['email'] == new_email:
            flash('New email must be different from the old email')
        else:
            user['email'] = new_email
            flash('Email changed successfully')
    
    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)