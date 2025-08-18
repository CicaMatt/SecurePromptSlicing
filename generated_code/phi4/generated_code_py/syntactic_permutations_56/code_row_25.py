from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database of users for demonstration purposes
users_db = {
    "user1": {"password": "password123", "email": "user1@example.com"},
}

def is_logged_in():
    return "username" in session

@app.route('/')
def index():
    if is_logged_in():
        username = session["username"]
        user_info = users_db.get(username, None)
        if user_info:
            email = user_info['email']
        else:
            email = "N/A"
        return render_template_string('''
            <h1>Welcome {{ username }}</h1>
            <p>Email: {{ email }}</p>
            <a href="/change_email">Change Email</a> |
            <a href="/logout">Logout</a>
        ''', username=username, email=email)
    else:
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user_info = users_db.get(username)

        if user_info and user_info['password'] == password:
            session["username"] = username
            return redirect(url_for('index'))
    
    return render_template_string('''
        <h1>Login</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))

    if request.method == 'POST':
        username = session['username']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user_info = users_db.get(username)
        
        if user_info and user_info['password'] == confirm_password:
            current_email = user_info['email']
            
            if new_email != current_email and '@' in new_email:
                users_db[username]['email'] = new_email
                return f"<h1>Email changed successfully to {new_email}</h1>"
    
    return render_template_string('''
        <h1>Change Email</h1>
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop("username", None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)