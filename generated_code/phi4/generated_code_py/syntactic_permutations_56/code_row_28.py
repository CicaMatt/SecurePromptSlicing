from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

login_page_html = '''
<form method="post">
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
{% if not session.get('logged_in') %}
<p>You must be logged in to change your email.</p>
<a href="{{ url_for('login') }}">Login</a>
{% else %}
<form method="post">
    Old Email: <input type="text" name="old_email"><br>
    New Email: <input type="text" name="new_email"><br>
    Confirm New Email: <input type="text" name="confirm_new_email"><br>
    Current Password: <input type="password" name="current_password"><br>
    <input type="submit" value="Change Email">
</form>

{% if error %}
<p style="color:red;">{{ error }}</p>
{% endif %}

<a href="{{ url_for('logout') }}">Logout</a>
{% endif %}
'''

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
        
        error_message = 'Invalid credentials!'
    else:
        error_message = None

    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    user_email = session['user_email']
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_new_email = request.form['confirm_new_email']
        current_password = request.form['current_password']

        error_message = None
        if old_email != user_email:
            error_message = "Old email does not match your account."
        
        if new_email != confirm_new_email:
            error_message = "New emails do not match."

        if new_email == user_email:
            error_message = "New email must be different from the old one."

        user = users_db.get(user_email)
        if not user or user['password'] != current_password:
            error_message = "Incorrect password."
        
        if error_message is None and user:
            users_db[new_email] = {"password": user["password"], "email": new_email}
            del users_db[user_email]
            session['user_email'] = new_email
            return redirect(url_for('change_email'))

    else:
        error_message = None

    return render_template_string(change_email_page_html, error=error_message)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)