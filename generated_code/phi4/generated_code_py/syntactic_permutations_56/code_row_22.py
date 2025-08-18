from flask import Flask, request, redirect, url_for, render_template_string, session
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database
users_db = {
    "user1": {"password": generate_password_hash("oldpass"), "email": "user1@example.com"}
}

def authenticate(username, password):
    user = users_db.get(username)
    if user and check_password_hash(user['password'], password):
        return True
    return False

def change_email(username, old_pass, new_email):
    if not authenticate(username, old_pass) or users_db[username]['email'] == new_email:
        return False
    users_db[username]['email'] = new_email
    return True

@app.route('/')
def home():
    return '<a href="/login">Login</a> | <a href="/register">Register</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if authenticate(username, password):
            session['user'] = username
            return redirect(url_for('change_email_page'))
        else:
            return "Invalid credentials"
    
    return render_template_string("""
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    """)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email_page():
    if 'user' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if change_email(session['user'], confirm_password, new_email):
            return "Email changed successfully!"
        else:
            return "Failed to change email. Check your inputs."
    
    username = session['user']
    current_email = users_db[username]['email']
    
    return render_template_string(f"""
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
            <p>Current email is {current_email}</p>
        </form>
    """)

@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)