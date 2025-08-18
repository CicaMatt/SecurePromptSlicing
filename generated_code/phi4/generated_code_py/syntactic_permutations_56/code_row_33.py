from flask import Flask, render_template_string, request, session, redirect, url_for

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simple in-memory "database" for demonstration purposes
users_db = {
    "user1": {"password": "pass123", "email": "old@example.com"}
}

login_page_template = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

profile_update_template = '''
{% if not logged_in %}
    <p>Please log in to update your profile.</p>
{% else %}
    <h2>Update Profile</h2>
    Old Email: {{ current_email }}<br><br>
    New Email: <input type="text" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Update Email">
{% endif %}
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        user = users_db.get(username)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['username'] = username
            return redirect(url_for('update_profile'))

    return render_template_string(login_page_template)

@app.route('/profile', methods=['GET', 'POST'])
def update_profile():
    logged_in = session.get('logged_in')
    if not logged_in:
        return redirect(url_for('login'))
    
    current_user = users_db[session['username']]
    current_email = current_user['email']
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if confirm_password != users_db[session['username']]['password']:
            return "Password confirmation failed. Please try again."

        if new_email == current_email:
            return "New email must be different from the old email."
        
        users_db[session['username']]['email'] = new_email
        return redirect(url_for('logout'))

    return render_template_string(profile_update_template, logged_in=logged_in, current_email=current_email)

@app.route('/logout')
def logout():
    session.clear()
    return "Logged out. <a href='/'>Login again</a>"

if __name__ == '__main__':
    app.run(debug=True)