from flask import Flask, request, session, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulating a database with in-memory storage
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
  <label for="email">Email:</label><br>
  <input type="text" id="email" name="email"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
'''

change_email_page = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
<form method="post">
  <label for="old_email">Old Email:</label><br>
  <input type="text" id="old_email" name="old_email"><br>
  <label for="new_email">New Email:</label><br>
  <input type="text" id="new_email" name="new_email"><br>
  <label for="confirm_password">Confirm Password:</label><br>
  <input type="password" id="confirm_password" name="confirm_password"><br><br>
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
            session['email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials!')

    return render_template_string(login_page)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        current_user_email = session.get('email')
        
        if old_email != current_user_email:
            flash('Old email does not match the logged in account!')
            return redirect(url_for('change_email'))
        
        user = users_db.get(old_email)
        if user and user['password'] == confirm_password and new_email not in users_db:
            users_db.pop(old_email)
            users_db[new_email] = {"password": user["password"], "email": new_email}
            session['email'] = new_email
            flash('Email changed successfully!')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials or email already exists!')

    return render_template_string(change_email_page)

if __name__ == '__main__':
    app.run(debug=True)