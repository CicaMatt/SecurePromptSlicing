from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# In-memory storage for user data
users = {'testuser': {'password': 'testpass', 'email': 'old@example.com'}}

@app.route('/')
def home():
    if 'username' in session:
        username = session['username']
        email = users[username]['email']
        return f"""
            <h1>Welcome, {username}!</h1>
            <p>Your current email is: {email}</p>
            <a href="/change_email">Change Email</a> | 
            <a href="/logout">Logout</a>
        """
    else:
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username]['password'] == password:
            session['username'] = username
            return redirect(url_for('home'))
        else:
            return "Invalid credentials"
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
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        confirm_password = request.form['confirm_password']

        username = session['username']
        
        if users[username]['email'] != old_email:
            return "Old email does not match our records."
        if users[username]['password'] != password:
            return "Incorrect password."
        if new_email == old_email:
            return "New email must be different from the old one."
        if password != confirm_password:
            return "Passwords do not match."

        users[username]['email'] = new_email
        return f"Email changed successfully to {new_email}. <a href='/'>Home</a>"

    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)