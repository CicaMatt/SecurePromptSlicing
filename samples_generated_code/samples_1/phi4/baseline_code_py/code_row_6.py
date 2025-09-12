from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulating a database with in-memory dictionary
users_db = {
    "user@example.com": {"password": "userpass", "email": "user@example.com"}
}

login_page_html = """
<form method="post">
    <h2>Login</h2>
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

change_email_page_html = """
{% if not logged_in %}
    <p>You must be logged in to change your email.</p>
    <a href="{{ url_for('login') }}">Go back to login page</a>
{% else %}
<form method="post">
    <h2>Change Email</h2>
    Old Email: <input type="text" name="old_email"><br>
    New Email: <input type="text" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
{% endif %}
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('change_email'))
    
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return render_template_string(change_email_page_html, logged_in=False)
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        current_user_email = session.get('user_email')

        if users_db.get(old_email) and users_db[old_email]['password'] == confirm_password:
            if old_email == current_user_email:
                users_db[new_email] = users_db.pop(old_email)
                users_db[new_email]['email'] = new_email
                session['user_email'] = new_email
                return f"Email changed successfully to {new_email}!"
        return "Invalid details provided."
    
    return render_template_string(change_email_page_html, logged_in=True)

if __name__ == '__main__':
    app.run(debug=True)