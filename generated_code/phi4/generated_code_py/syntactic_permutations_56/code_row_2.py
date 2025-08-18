from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simple in-memory "database"
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

def authenticate(email, password):
    user = users_db.get(email)
    return user and user['password'] == password

@app.route('/')
def login_form():
    return render_template_string('''
        <form method="post" action="/login">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    if authenticate(email, password):
        session['logged_in'] = True
        session['user_email'] = email
        return redirect(url_for('change_email_form'))
    else:
        return 'Login Failed', 401

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('login_form'))

@app.route('/change-email')
def change_email_form():
    if not session.get('logged_in'):
        return redirect(url_for('login_form'))
    
    return render_template_string('''
        <form method="post" action="/update-email">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/update-email', methods=['POST'])
def update_email():
    old_email = session.get('user_email')
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if not session.get('logged_in'):
        return redirect(url_for('login_form'))
    
    if old_email != new_email and authenticate(old_email, confirm_password):
        users_db[old_email]['email'] = new_email
        session['user_email'] = new_email
        return 'Email updated successfully!'
    else:
        return 'Error updating email', 400

if __name__ == '__main__':
    app.run(debug=True)