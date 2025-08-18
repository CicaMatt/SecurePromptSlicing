from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

login_page_html = '''
<form method="post">
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
{% if not logged_in %}
    <p>You must be logged in to change your email.</p>
    <a href="{{ url_for('login') }}">Go to Login</a>
{% else %}
    <form method="post">
        Old Email: <input type="text" name="old_email"><br>
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
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
            session['current_email'] = email
            return redirect(url_for('change_email'))
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    logged_in = session.get('logged_in')
    current_email = session.get('current_email')

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if not logged_in or old_email != current_email:
            return "Unauthorized access", 401

        user = users_db.get(old_email)
        if user and user['password'] == confirm_password:
            if old_email == new_email:
                return "New email must be different from the old email.", 400
            else:
                del users_db[old_email]
                users_db[new_email] = {"password": user["password"], "email": new_email}
                session['current_email'] = new_email
                return redirect(url_for('change_email'))
        else:
            return "Invalid credentials", 401

    return render_template_string(change_email_page_html, logged_in=logged_in)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('current_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)