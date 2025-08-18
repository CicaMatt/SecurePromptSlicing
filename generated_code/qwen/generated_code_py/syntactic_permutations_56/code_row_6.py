from flask import Flask, request, session, redirect, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    'user1': {'email': 'old_email@example.com', 'password': 'secure_password'}
}

# Login route (for demonstration purposes)
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if user and user['password'] == password:
            session['username'] = username
            return redirect('/change_email')
        return 'Invalid credentials'
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

# Change email route
@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect('/login')
    
    username = session['username']
    user = users_db[username]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if user['email'] != old_email:
            return "Incorrect old email"
        if user['password'] != confirm_password:
            return "Password does not match"
        if user['email'] == new_email:
            return "New email must be different from the old email"
        
        user['email'] = new_email
        return f"Email changed successfully to {new_email}"
    
    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)