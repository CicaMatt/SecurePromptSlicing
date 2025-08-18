from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulating a database of users with passwords and emails
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

@app.route('/')
def login():
    if 'logged_in' in session:
        return redirect(url_for('change_email'))
    
    return '''
    <form method="post" action="/login">
      Email: <input type="text" name="email"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    '''

@app.route('/login', methods=['POST'])
def authenticate():
    email = request.form['email']
    password = request.form['password']
    
    if email in users_db and users_db[email]['password'] == password:
        session['logged_in'] = True
        session['user_email'] = email
        return redirect(url_for('change_email'))
    
    return 'Login Failed. <a href="/">Try Again</a>'

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = session['user_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email in users_db and users_db[old_email]['password'] == confirm_password:
            if new_email not in users_db:  # Check if the new email already exists
                users_db[new_email] = users_db.pop(old_email)
                users_db[new_email]['email'] = new_email
                session['user_email'] = new_email
                return 'Email changed successfully.'
        return 'Password incorrect or new email already in use.'

    return '''
    <form method="post" action="/change-email">
      Old Email: <input type="text" name="old_email" value="{email}" readonly><br>
      New Email: <input type="text" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <input type="submit" value="Change Email">
    </form>
    '''.format(email=session['user_email'])

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)