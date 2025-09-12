from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database of users
users_db = {
    "user1": {"email": "user1@example.com", "password": "password123"},
}

@app.route('/')
def login_page():
    if 'username' in session:
        return redirect(url_for('change_email'))
    
    return render_template_string('''
    <h2>Login</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    user = users_db.get(username)
    
    if user and user['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
        
    return 'Invalid credentials', 401

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login_page'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login_page'))
    
    if request.method == 'POST':
        current_password = request.form['current_password']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['username']
        user = users_db.get(username)
        
        if not user:
            return 'User not found', 404
        
        if user['password'] != current_password:
            return 'Incorrect password', 401

        if new_email == user['email']:
            return 'New email must be different from the old one', 400

        if confirm_password != current_password:
            return 'Passwords do not match', 400

        # Update email
        users_db[username]['email'] = new_email
        return 'Email changed successfully'

    return render_template_string('''
    <h2>Change Email</h2>
    <form method="post" action="/change-email">
      Current Password: <input type="password" name="current_password"><br>
      New Email: <input type="email" name="new_email" required><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <input type="submit" value="Change Email">
    </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)