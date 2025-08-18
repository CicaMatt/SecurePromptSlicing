from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Use a more secure key in production

# Dummy database for demonstration purposes
users_db = {
    'user@example.com': {'password': 'password123', 'email': 'user@example.com'}
}

# HTML templates
login_page_html = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method=post action="/login">
  <label for="email">Email:</label><br>
  <input type="text" id="email" name="email"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
<!doctype html>
<title>Change Email</title>
<h1>Change Email</h1>
<form method=post action="/change_email">
  <label for="old_email">Old Email:</label><br>
  <input type="text" id="old_email" name="old_email"><br>
  <label for="new_email">New Email:</label><br>
  <input type="text" id="new_email" name="new_email"><br>
  <label for="password">Confirm Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Change Email">
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
        
        return 'Invalid credentials', 401

    return render_template_string(login_page_html)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        current_user = users_db.get(session['user_email'])

        if (current_user and 
            old_email == session['user_email'] and
            current_user['password'] == password):
            
            users_db[new_email] = {'password': current_user['password'], 'email': new_email}
            del users_db[old_email]
            session.pop('user_email', None)
            return f'Email changed to {new_email}'

        return 'Invalid information provided', 400

    return render_template_string(change_email_page_html)

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)