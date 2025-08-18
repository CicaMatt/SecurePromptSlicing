from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
users_db = {
    "user1": {"password": "pass123", "email": "user1@example.com"}
}

def check_credentials(username, password):
    user = users_db.get(username)
    if user and user["password"] == password:
        return True
    return False

def change_email(old_email, new_email, current_password, confirm_password):
    for username, details in users_db.items():
        if details["email"] == old_email and check_credentials(username, current_password):
            if new_email != old_email and new_email not in [user['email'] for user in users_db.values()]:
                if new_email == confirm_password:
                    users_db[username]["email"] = new_email
                    return True
    return False

@app.route('/')
def home():
    if 'username' in session:
        username = session['username']
        email = users_db[username]['email']
        return render_template_string('''
            <h1>Welcome {{ username }}!</h1>
            <p>Your current email: {{ email }}</p>
            <a href="/change_email">Change Email</a> |
            <a href="/logout">Logout</a>
        ''', username=username, email=email)
    return render_template_string('''
        <h1>Login Page</h1>
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
    if check_credentials(username, password):
        session['username'] = username
        return redirect(url_for('home'))
    return 'Invalid credentials. Please try again.'

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('home'))

@app.route('/change_email')
def change_email_form():
    if 'username' not in session:
        return redirect(url_for('home'))
    username = session['username']
    email = users_db[username]['email']
    return render_template_string('''
        <h1>Change Email</h1>
        <form method="post" action="/update_email">
            Old Email: <input type="text" name="old_email" value="{{ email }}" readonly><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''', email=email)

@app.route('/update_email', methods=['POST'])
def update_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']
    username = session.get('username')
    
    if change_email(old_email, new_email, users_db[username]["password"], confirm_password):
        return 'Email updated successfully!'
    else:
        return 'Failed to update email. Check your details and try again.'

if __name__ == '__main__':
    app.run(debug=True)