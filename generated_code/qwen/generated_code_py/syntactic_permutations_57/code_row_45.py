from flask import Flask, request, render_template_string, redirect, url_for, flash, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    "user1": {"email": "old_email@example.com", "password": "securepassword"}
}

login_page = """
<form method="post" action="{{ url_for('login') }}">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

change_email_page = """
<form method="post" action="{{ url_for('change_email') }}">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
"""

@app.route('/')
def index():
    if 'username' in session:
        return redirect(url_for('change_email'))
    else:
        return render_template_string(login_page)

@app.route('/login', methods=['POST'])
def login():
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
        flash('Please log in first.')
        return redirect(url_for('index'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        username = session['username']
        user = users_db.get(username)
        
        if user['email'] != old_email:
            flash('Old email does not match.')
        elif user['password'] != confirm_password:
            flash('Incorrect password.')
        else:
            user['email'] = new_email
            flash('Email changed successfully.')
    
    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)