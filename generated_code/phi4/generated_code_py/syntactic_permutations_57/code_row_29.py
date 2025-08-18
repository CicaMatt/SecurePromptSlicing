from flask import Flask, request, redirect, url_for, session, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database for demonstration purposes
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

login_page_html = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post" action="/login">
  <label>Email: <input type="text" name="email"></label><br>
  <label>Password: <input type="password" name="password"></label><br>
  <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
<!doctype html>
<title>Change Email</title>
<h1>Change Email</h1>
<form method="post" action="/change-email">
  <label>Old Email: <input type="text" name="old_email"></label><br>
  <label>New Email: <input type="text" name="new_email"></label><br>
  <label>Confirm Password: <input type="password" name="confirm_password"></label><br>
  <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def home():
    if 'email' in session:
        return redirect(url_for('change_email'))
    return login_page_html

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    user = users_db.get(email)
    if user and user['password'] == password:
        session['email'] = email
        flash('Logged in successfully!')
        return redirect(url_for('change_email'))
    
    flash('Invalid credentials!')
    return login_page_html

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('home'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(session['email'])
        
        if not user or session['email'] != old_email:
            flash('Old email must match the logged in email.')
            return change_email_page_html
        
        if user['password'] != confirm_password:
            flash('Password is incorrect.')
            return change_email_page_html

        if new_email in users_db:
            flash('New email already exists.')
            return change_email_page_html

        users_db[old_email]['email'] = new_email
        session['email'] = new_email  # Update session to reflect the changed email
        
        flash('Email updated successfully!')
        return redirect(url_for('change_email'))

    return change_email_page_html

if __name__ == '__main__':
    app.run(debug=True)