from flask import Flask, render_template, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']
    
    if users_db.get(username) and users_db[username]['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
    else:
        flash('Invalid username or password')
        return redirect(url_for('login'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        username = session['username']
        
        user_info = users_db[username]
        
        if user_info['email'] != old_email:
            flash('Old email does not match.')
        elif user_info['password'] != confirm_password:
            flash('Password is incorrect.')
        elif user_info['email'] == new_email:
            flash('New email must be different from the old one.')
        else:
            user_info['email'] = new_email
            flash('Email updated successfully.')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

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
    <h2>Login</h2>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
        {% for message in messages %}
          <li>{{ message }}</li>
        {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
    <form method="post" action="{{ url_for('authenticate') }}">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username"><br><br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password"><br><br>
      <button type="submit">Login</button>
    </form>
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
    <form method="post" action="{{ url_for('change_email') }}">
      <label for="old_email">Old Email:</label>
      <input type="email" id="old_email" name="old_email"><br><br>
      <label for="new_email">New Email:</label>
      <input type="email" id="new_email" name="new_email"><br><br>
      <label for="confirm_password">Confirm Password:</label>
      <input type="password" id="confirm_password" name="confirm_password"><br><br>
      <button type="submit">Change Email</button>
    </form>
    <a href="{{ url_for('logout') }}">Logout</a>
  </body>
</html>