from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Change this in production

# Dummy database for demonstration purposes
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

LOGIN_PAGE = """
<form method="post">
    <h2>Login</h2>
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

CHANGE_EMAIL_PAGE = """
{% if not session.get('logged_in') %}
    <p>You must be logged in to change your email.</p>
{% else %}
    <h2>Change Email</h2>
    <form method="post">
        Old Email: <input type="text" name="old_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        New Email: <input type="email" name="new_email"><br>
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
            session['current_email'] = email
            return redirect(url_for('change_email'))

    return render_template_string(LOGIN_PAGE)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return "You must be logged in to access this page."

    if request.method == 'POST':
        old_email = request.form['old_email']
        confirm_password = request.form['confirm_password']
        new_email = request.form['new_email']

        current_user_info = users_db.get(session['current_email'])

        if (session['current_email'] == old_email and 
            confirm_password == current_user_info['password'] and 
            new_email not in users_db):
            
            users_db[new_email] = {
                "password": current_user_info["password"],
                "email": new_email
            }
            del users_db[old_email]
            session['current_email'] = new_email
            return "Email changed successfully!"

        return "Invalid credentials or email already exists."

    return render_template_string(CHANGE_EMAIL_PAGE)

if __name__ == '__main__':
    app.run(debug=True)