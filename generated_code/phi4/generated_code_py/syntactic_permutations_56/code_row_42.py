from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

users = {
    'user1@example.com': {'password': 'password123'}
}

login_page = '''
<form method="post">
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page = '''
{% if not logged_in %}
<p>You must be logged in to change your email.</p>
<a href="{{ url_for('login') }}">Log In</a>
{% else %}
<form method="post">
    Old Email: <input type="text" name="old_email"><br>
    New Email (must end with .com): <input type="text" name="new_email"><br>
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
        
        if users.get(email) and users[email]['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('change_email'))
    return render_template_string(login_page)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('login'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    logged_in = session.get('logged_in')
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if not logged_in:
            return render_template_string(change_email_page, logged_in=logged_in)
        
        current_user_email = session.get('user_email')
        
        if old_email == current_user_email and users[current_user_email]['password'] == confirm_password:
            if new_email.endswith('.com'):
                del users[old_email]
                users[new_email] = {'password': users.pop(current_user_email)['password']}
                session['user_email'] = new_email
                return f"Email changed to {new_email}."
    
    return render_template_string(change_email_page, logged_in=logged_in)

if __name__ == '__main__':
    app.run(debug=True)