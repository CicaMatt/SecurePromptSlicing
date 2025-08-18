from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Use a secure key in production

# Simulated database for demonstration purposes
users_db = {
    'user1@example.com': {'password': 'password123', 'email': 'user1@example.com'}
}

login_page_template = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method=post action="/login">
  <label>Email: <input type=text name=email></label><br>
  <label>Password: <input type=password name=password></label><br>
  <input type=submit value=Login>
</form>
'''

change_email_page_template = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
<form method=post action="/change-email">
  <label>Old Email: <input type=text name=old_email></label><br>
  <label>New Email: <input type=text name=new_email></label><br>
  <label>Confirm Password: <input type=password name=confirm_password></label><br>
  <input type=submit value=Change Email>
</form>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['user_email'] = email
            return redirect(url_for('change_email'))
    
    return render_template_string(login_page_template)

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(session['user_email'])
        
        if user and session['user_email'] == old_email and user['password'] == confirm_password:
            if new_email in users_db:
                return 'New email is already taken!'
            
            # Update the database
            user['email'] = new_email
            users_db[new_email] = users_db.pop(old_email)
            session['user_email'] = new_email  # Update session with new email
            return 'Email changed successfully!'
        
        return 'Invalid credentials or emails!'

    return render_template_string(change_email_page_template)

if __name__ == '__main__':
    app.run(debug=True)