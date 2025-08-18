from flask import Flask, request, redirect, url_for, render_template_string, flash, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# In-memory storage for simplicity; replace with database in production.
users = {'user1': {'password': 'pass123', 'email': 'user1@example.com'}}

login_page_html = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <h2>Login</h2>
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <button type="submit">Login</button>
    </form>
  </body>
</html>
'''

change_email_page_html = '''
<!doctype html>
<html lang="en">
  <head><title>Change Email</title></head>
  <body>
    <h2>Change Email</h2>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
          {% for message in messages %}
            <li>{{ message }}</li>
          {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
    <form method="post">
      Old Email: <input type="text" name="old_email"><br>
      New Email: <input type="email" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <button type="submit">Change Email</button>
    </form>
  </body>
</html>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        user = users.get(username)
        if user and user['password'] == password:
            session['user'] = username
            return redirect(url_for('change_email'))
        else:
            flash("Invalid credentials")
    return render_template_string(login_page_html)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user_info = users[session['user']]
        
        # Check if old email matches the current one
        if user_info['email'] != old_email:
            flash("Old email does not match.")
        elif new_email == old_email:
            flash("New email must be different from old email.")
        elif confirm_password != user_info['password']:
            flash("Password is incorrect.")
        else:
            users[session['user']]['email'] = new_email
            flash("Email changed successfully.")

    return render_template_string(change_email_page_html)

@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)