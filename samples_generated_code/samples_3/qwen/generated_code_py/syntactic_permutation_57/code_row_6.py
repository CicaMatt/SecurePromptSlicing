from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    'user1': {'old_email': 'user1@example.com', 'password': 'securepassword'}
}

login_page = '''
<form action="/login" method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page = '''
<form action="/change_email" method="post">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def index():
    if 'username' in session:
        return f'<p>Logged in as {session["username"]}</p><a href="/change_email">Change Email</a>'
    return login_page

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user_data = users_db.get(username)
    
    if user_data and user_data['password'] == password:
        session['username'] = username
        return redirect(url_for('index'))
    else:
        return 'Invalid username or password', 401

@app.route('/change_email', methods=['GET'])
def change_email_form():
    if 'username' not in session:
        return redirect(url_for('index'))
    return change_email_page

@app.route('/change_email', methods=['POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('index'))
    
    username = session['username']
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']
    
    user_data = users_db.get(username)
    
    if user_data and user_data['old_email'] == old_email and user_data['password'] == confirm_password:
        user_data['old_email'] = new_email
        return 'Email changed successfully'
    else:
        return 'Incorrect old email or password', 401

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)