from flask import Flask, render_template, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database
users_db = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

@app.route('/')
def home():
    if 'username' in session:
        return f"Welcome {session['username']}. Your email is {users_db[session['username']]['email']}. <a href='/change_email'>Change Email</a> <a href='/logout'>Logout</a>"
    return "You are not logged in. Please log in."

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username]['password'] == password:
            session['username'] = username
            return redirect(url_for('home'))
        else:
            flash("Invalid credentials")
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db[session['username']]
        
        if user['email'] != old_email:
            flash("Old email does not match.")
        elif user['password'] != confirm_password:
            flash("Password confirmation failed.")
        else:
            user['email'] = new_email
            flash("Email updated successfully.")
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/login.html -->
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
        {% for message in messages %}
          <li>{{ message }}</li>
        {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
  </body>
</html>



<!-- templates/change_email.html -->
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Change Email</title>
  </head>
  <body>
    <h1>Change Email</h1>
    <form method="post">
      Old Email: <input type="email" name="old_email"><br>
      New Email: <input type="email" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <input type="submit" value="Change Email">
    </form>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
        {% for message in messages %}
          <li>{{ message }}</li>
        {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
  </body>
</html>