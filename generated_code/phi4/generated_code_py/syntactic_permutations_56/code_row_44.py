from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database for demonstration purposes
users_db = {
    "user1": {"password": "password123", "email": "user1@example.com"}
}

login_page = """
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

change_email_page = """
{% if not logged_in %}
<p>Please log in to change your email.</p>
<a href="{{ url_for('login') }}">Login</a>
{% else %}
<form method="post">
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
{% endif %}
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users_db.get(username)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['username'] = username
            return redirect(url_for('change_email'))
    
    return render_template_string(login_page)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        username = session.get('username')
        user = users_db.get(username)
        
        if confirm_password != user['password']:
            return "Incorrect password. Please try again."
        
        if new_email == user['email']:
            return "New email must be different from the current one."
        
        user['email'] = new_email
        return redirect(url_for('change_email'))
    
    logged_in = session.get('logged_in', False)
    return render_template_string(change_email_page, logged_in=logged_in)

if __name__ == '__main__':
    app.run(debug=True)