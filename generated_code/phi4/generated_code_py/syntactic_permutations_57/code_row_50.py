from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# In-memory database for demonstration purposes.
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

login_page_html = """
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
  Email: <input type="text" name="email"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

change_email_page_html = """
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
<form method="post">
  Old Email: <input type="text" name="old_email"><br>
  New Email: <input type="text" name="new_email"><br>
  Confirm Password: <input type="password" name="confirm_password"><br>
  <input type="submit" value="Change Email">
</form>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials", 401
    
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(session['user_email'])

        if (user and
            user['email'] == old_email and
            user['password'] == confirm_password and
            new_email not in users_db):
            
            users_db[new_email] = {'password': user['password'], 'email': new_email}
            del users_db[old_email]

            session['user_email'] = new_email
            return "Email changed successfully"
        else:
            return "Invalid information", 400

    return render_template_string(change_email_page_html)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)