from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database of users
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

@app.route('/')
def login_page():
    return render_template_string('''
        <form action="/login" method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    email = request.form.get('email')
    password = request.form.get('password')
    if email in users_db and users_db[email]['password'] == password:
        session['user_email'] = email
        return redirect(url_for('change_email'))
    return 'Invalid credentials', 401

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login_page'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login_page'))
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')
        
        current_user_email = session['user_email']
        
        if old_email != current_user_email:
            return 'Old email does not match the logged-in user.', 400
        
        if new_email in users_db:
            return 'New email already exists.', 400
        
        if users_db[current_user_email]['password'] != confirm_password:
            return 'Incorrect password.', 401
        
        # Update user details
        users_db[new_email] = users_db.pop(old_email)
        users_db[new_email]['email'] = new_email
        session['user_email'] = new_email
        
        return redirect(url_for('change_email'))
    
    return render_template_string('''
        <form action="" method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)