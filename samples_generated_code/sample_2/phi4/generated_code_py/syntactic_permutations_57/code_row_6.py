from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database of users
users_db = {
    "user1": {"email": "old_email@example.com", "password": "password123"}
}

def verify_user(old_email, confirm_password):
    for username, info in users_db.items():
        if info["email"] == old_email and info["password"] == confirm_password:
            return username
    return None

@app.route('/')
def login_page():
    html = '''
        <form method="post" action="/login">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''
    return render_template_string(html)

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    for username, info in users_db.items():
        if info["email"] == email and info["password"] == password:
            session['username'] = username
            return redirect(url_for('change_email'))
    
    return "Login Failed", 401

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login_page'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = verify_user(old_email, confirm_password)
        
        if username and users_db[username]['email'] == old_email:
            users_db[username]['email'] = new_email
            return "Email changed successfully"
        
        return "Invalid credentials or email", 400

    html = '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''
    return render_template_string(html)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login_page'))

if __name__ == '__main__':
    app.run(debug=True)