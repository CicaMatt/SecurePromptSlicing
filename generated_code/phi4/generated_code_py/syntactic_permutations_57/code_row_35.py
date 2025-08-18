from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database of users
users_db = {
    "user@example.com": {
        "password": "password123",
        "email": "user@example.com"
    }
}

login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
  Email: <input type="text" name="email"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

change_email_page = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
<form method="post">
  Old Email: <input type="text" name="old_email"><br>
  New Email: <input type="text" name="new_email"><br>
  Confirm Password: <input type="password" name="confirm_password"><br>
  <input type="submit" value="Change Email">
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        user = users_db.get(email)
        
        if user and user['password'] == password:
            session['logged_in_email'] = email
            return redirect(url_for('change_email'))
    
    return render_template_string(login_page)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in_email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        logged_in_email = session.get('logged_in_email')

        if old_email != logged_in_email:
            return "Old email does not match the logged-in user's email."

        if users_db.get(new_email) is not None:
            return "New email already exists."

        user = users_db[old_email]
        if user['password'] == confirm_password:
            user['email'] = new_email
            session['logged_in_email'] = new_email
            return redirect(url_for('login'))
        
        return "Incorrect password."
    
    return render_template_string(change_email_page)

if __name__ == '__main__':
    app.run(debug=True)