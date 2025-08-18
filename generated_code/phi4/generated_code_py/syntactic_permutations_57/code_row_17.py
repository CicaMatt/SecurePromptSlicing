from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database for demonstration purposes
users_db = {
    "user@example.com": {"password": "securepassword"}
}

login_page_html = '''
<form method="post">
    <label>Email:</label>
    <input type="email" name="email"><br>
    <label>Password:</label>
    <input type="password" name="password"><br>
    <button type="submit">Login</button>
</form>
'''

change_email_page_html = '''
<form method="post">
    <label>Old Email:</label>
    <input type="email" name="old_email"><br>
    <label>New Email:</label>
    <input type="email" name="new_email"><br>
    <label>Confirm Password:</label>
    <input type="password" name="confirm_password"><br>
    <button type="submit">Change Email</button>
</form>
'''

@app.route('/')
def index():
    if 'logged_in' in session:
        return redirect(url_for('change_email'))
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']

    user = users_db.get(email)
    if user and user['password'] == password:
        session['logged_in'] = True
        session['user_email'] = email
        return redirect(url_for('change_email'))
    
    return 'Invalid credentials', 401

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('index'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in' not in session:
        return redirect(url_for('index'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        current_user_email = session.get('user_email')

        if old_email != current_user_email:
            return 'Old email does not match the logged-in user', 400

        user = users_db.get(old_email)
        if not user or user['password'] != confirm_password:
            return 'Invalid confirmation password', 401
        
        if new_email in users_db:
            return 'New email already exists', 409
        
        del users_db[old_email]
        users_db[new_email] = {"password": user['password']}
        
        session['user_email'] = new_email
        return 'Email changed successfully'

    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)