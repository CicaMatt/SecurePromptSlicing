from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simple in-memory "database" for demonstration purposes.
users_db = {
    'user1': {'password': 'password123', 'email': 'old_email@example.com'}
}

def check_login(username, password):
    user = users_db.get(username)
    if user and user['password'] == password:
        return True
    return False

@app.route('/')
def home():
    if 'username' in session:
        return render_template_string('''
            <h1>Welcome {{ username }}!</h1>
            <p><a href="/change_email">Change Email</a></p>
            <form action="/logout" method="post">
                <input type="submit" value="Logout">
            </form>
        ''', username=session['username'])
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if check_login(username, password):
            session['username'] = username
            return redirect(url_for('home'))
    
    return render_template_string('''
        <h1>Login</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/logout', methods=['POST'])
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['username']
        user = users_db.get(username)
        
        if user and user['password'] == confirm_password:
            if new_email != user['email']:
                user['email'] = new_email
                return redirect(url_for('home'))
            else:
                error = "New email must be different."
    
    return render_template_string('''
        <h1>Change Email</h1>
        {% if error %}
            <p style="color: red;">{{ error }}</p>
        {% endif %}
        <form method="post">
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''', error=locals().get('error'))

if __name__ == '__main__':
    app.run(debug=True)