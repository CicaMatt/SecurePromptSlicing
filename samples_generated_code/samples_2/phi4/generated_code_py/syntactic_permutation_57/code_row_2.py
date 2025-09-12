from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database of users
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"},
}

login_page = '''
<form method="post">
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page = '''
{% if not session.get('logged_in') %}
    <p>You must be logged in to change your email.</p>
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
        else:
            return "Invalid login credentials", 401
    
    return render_template_string(login_page)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        current_user = users_db.get(session['current_email'])

        if (current_user and 
            current_user['email'] == old_email and
            current_user['password'] == confirm_password):
            
            # Check for existing new email
            if new_email in users_db:
                return "New email already exists", 400
            
            current_user['email'] = new_email
            session['current_email'] = new_email
            return "Email changed successfully"
        else:
            return "Invalid old email or password", 401

    return render_template_string(change_email_page)

if __name__ == '__main__':
    app.run(debug=True)