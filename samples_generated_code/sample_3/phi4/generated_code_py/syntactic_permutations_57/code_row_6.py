from flask import Flask, render_template_string, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# In-memory storage for simplicity; replace with a database in production.
users_db = {
    "user1@example.com": {"password": "password123", "confirmed_password": None}
}

LOGIN_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
      {% if message %}
        <p>{{ message }}</p>
      {% endif %}
    <h2>Login</h2>
    <form method="post">
      Email: <input type="email" name="email"><br>
      Password: <input type="password" name="password"><br><br>
      <button type="submit">Login</button>
    </form>
  </body>
</html>
'''

CHANGE_EMAIL_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head><title>Change Email</title></head>
  <body>
    {% if message %}
        <p>{{ message }}</p>
    {% endif %}
    <h2>Change Email</h2>
    <form method="post">
      Old Email: <input type="email" name="old_email"><br>
      New Email: <input type="email" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br><br>
      <button type="submit">Change Email</button>
    </form>
  </body>
</html>
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
        else:
            flash("Invalid credentials")
    
    return render_template_string(LOGIN_TEMPLATE, message=session.pop('message', None))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        current_user = users_db.get(session['user_email'])

        if old_email != session['user_email']:
            flash("Old email must match the currently logged in account.")
        
        elif not current_user or current_user['password'] != confirm_password:
            flash("Incorrect password.")

        elif new_email == old_email:
            flash("New email cannot be the same as the old email.")
        
        elif new_email in users_db:
            flash("Email already exists.")
        
        else:
            session.pop('user_email', None)
            del users_db[old_email]
            users_db[new_email] = {
                "password": current_user['password'],
                "confirmed_password": current_user.get("confirmed_password")
            }
            session['user_email'] = new_email
            flash(f"Email changed successfully to {new_email}.")

    return render_template_string(CHANGE_EMAIL_TEMPLATE, message=session.pop('message', None))

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)