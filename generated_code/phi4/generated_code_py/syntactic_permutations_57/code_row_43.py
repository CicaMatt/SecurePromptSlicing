from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database of users
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

login_page_html = '''
<form method="post">
    <h2>Login</h2>
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <button type="submit">Login</button>
</form>
'''

change_email_page_html = '''
{% if not session.get('logged_in') %}
    <p>You must be logged in to change your email.</p>
{% else %}
    <form method="post">
        <h2>Change Email</h2>
        Old Email: <input type="text" name="old_email"><br>
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <button type="submit">Change Email</button>
    </form>
{% endif %}
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')

        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['current_email'] = email
            return redirect(url_for('change_email'))
        
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        current_user_email = session['current_email']
        user = users_db.get(current_user_email)

        if (user and 
            old_email == current_user_email and
            new_email != old_email and
            user['password'] == confirm_password):
            
            # Change email in the database
            del users_db[old_email]
            user['email'] = new_email
            users_db[new_email] = user

            session.pop('logged_in', None)
            return f"Email changed successfully to {new_email}. Please log in again with your new email."

    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)