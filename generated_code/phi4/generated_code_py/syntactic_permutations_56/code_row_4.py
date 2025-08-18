from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration purposes
users_db = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

@app.route('/')
def login_page():
    return render_template_string('''
        <h2>Login</h2>
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''), request.method

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    if username in users_db and users_db[username]['password'] == password:
        session['logged_in'] = True
        session['user'] = username
        return redirect(url_for('change_email'))
    
    return 'Invalid credentials', 401

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user', None)
    return redirect(url_for('login_page'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login_page'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session.get('user')
        user_data = users_db.get(username)

        if not user_data:
            return 'User not found', 404

        if user_data['email'] != old_email:
            return 'Old email does not match our records.', 400
        
        if new_email == old_email:
            return 'New email must be different from the old email.', 400
        
        if confirm_password != user_data['password']:
            return 'Password is incorrect.', 401

        users_db[username]['email'] = new_email
        return f'Email updated to {new_email} successfully!'

    return render_template_string('''
        <h2>Change Email</h2>
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)