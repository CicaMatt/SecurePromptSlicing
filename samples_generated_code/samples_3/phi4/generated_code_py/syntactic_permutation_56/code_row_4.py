from flask import Flask, request, redirect, url_for, render_template_string, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simple in-memory storage for demonstration purposes
users = {
    'user@example.com': {'password': 'password123', 'email': 'user@example.com'}
}

login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method=post action="/change_email">
  <label>Email: <input type=text name=email></label><br>
  <label>Password: <input type=password name=password></label><br>
  <input type=submit value="Change Email">
</form>
'''

change_email_page = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Your Email</h2>
<form method=post action="/update_email">
  <label>Old Email: <input type=text name=old_email readonly></label><br>
  <label>New Email: <input type=text name=new_email></label><br>
  <label>Password: <input type=password name=password></label><br>
  <input type=submit value="Update Email">
</form>
'''

@app.route('/')
def index():
    return login_page

@app.route('/change_email', methods=['POST'])
def change_email():
    email = request.form['email']
    password = request.form['password']
    
    if email in users and users[email]['password'] == password:
        old_email = email
        response = redirect(url_for('update_email', old_email=old_email))
        response.set_cookie('old_email', old_email)
        return response
    else:
        flash('Invalid credentials')
        return login_page

@app.route('/change', methods=['GET'])
def update_email():
    return change_email_page

@app.route('/update_email', methods=['POST'])
def update():
    old_email = request.cookies.get('old_email')
    new_email = request.form['new_email']
    password = request.form['password']

    if old_email not in users:
        flash('Session expired or invalid session.')
        return redirect(url_for('index'))

    if users[old_email]['password'] != password:
        flash('Incorrect password.')
        return change_email_page
    
    if new_email == old_email:
        flash('New email must be different from the old email.')
        return change_email_page

    if new_email in users:
        flash('Email already exists.')
        return change_email_page

    users[new_email] = {'password': users[old_email]['password'], 'email': new_email}
    del users[old_email]

    flash('Email updated successfully!')
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)