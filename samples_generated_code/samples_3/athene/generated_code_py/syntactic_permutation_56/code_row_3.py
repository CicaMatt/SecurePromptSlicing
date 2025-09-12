from flask import Flask, request, redirect, url_for, render_template, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users = {
    "user1": {
        "password": "pass1",
        "email": "user1@example.com"
    }
}

@app.route('/')
def index():
    if 'username' in session:
        return f"Logged in as {session['username']}<br><a href='/change_email'>Change Email</a> <a href='/logout'>Logout</a>"
    return 'You are not logged in. <a href="/login">Login here</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username]['password'] == password:
            session['username'] = username
            return redirect(url_for('index'))
        else:
            return 'Invalid credentials'
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if users[session['username']]['email'] == new_email:
            return "New email must be different from the current email."
        
        if users[session['username']]['password'] != confirm_password:
            return "Incorrect password."
        
        users[session['username']]['email'] = new_email
        return "Email updated successfully."

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)