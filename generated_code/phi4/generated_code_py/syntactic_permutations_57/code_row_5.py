from flask import Flask, request, session, redirect, url_for, render_template_string
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database for demonstration purposes
users_db = {
    'user1@example.com': {'password': 'pbkdf2:sha256:150000$...', 'email': 'user1@example.com'},
}

login_page_html = '''
<form method="post">
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
<form method="post">
    Old Email: <input type="text" name="old_email"><br>
    New Email: <input type="text" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def index():
    if 'user' in session:
        return redirect(url_for('change_email'))
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    user = users_db.get(email)
    if user and check_password_hash(user['password'], password):
        session['user'] = email
        return redirect(url_for('change_email'))
    
    return 'Login Failed', 401

@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect(url_for('index'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('index'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(session['user'])
        
        if user and old_email == session['user'] and check_password_hash(user['password'], confirm_password):
            if new_email in users_db:
                return 'New email already exists', 400
            users_db[new_email] = {'password': user['password']}
            del users_db[old_email]
            session['user'] = new_email
            return 'Email changed successfully'
        
        return 'Invalid credentials or confirmation password', 401
    
    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)