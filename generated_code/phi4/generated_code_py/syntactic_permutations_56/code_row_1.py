from flask import Flask, request, session, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
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
        else:
            flash('Invalid credentials!')
    return render_template_string(login_page_html)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return "You must be logged in to access this page."
    
    current_email = session['current_email']
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != current_email:
            flash('Old email does not match your logged-in credentials.')
            return render_template_string(change_email_page_html)

        user = users_db.get(old_email)
        if not user or user['password'] != confirm_password:
            flash('Incorrect password!')
            return render_template_string(change_email_page_html)
        
        if old_email == new_email:
            flash('New email must be different from the old one.')
            return render_template_string(change_email_page_html)

        users_db[new_email] = {"password": user['password'], "email": new_email}
        del users_db[old_email]

        session['current_email'] = new_email
        flash('Email changed successfully!')
        return redirect(url_for('change_email'))
    
    return render_template_string(change_email_page_html)

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)