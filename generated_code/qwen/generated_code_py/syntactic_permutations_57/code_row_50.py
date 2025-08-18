from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    'user1@example.com': {'password_hash': 'pbkdf2:sha256:150000$abc123$def456'},  # Example hash for password 'secret'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and check_password_hash(user['password_hash'], password):
            session['user_email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid email or password')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))
    
    current_user = users_db.get(session['user_email'])
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != session['user_email']:
            flash('Old email does not match the logged in user')
        elif not check_password_hash(current_user['password_hash'], confirm_password):
            flash('Incorrect password')
        elif new_email in users_db:
            flash('New email is already registered')
        else:
            # Update email in database
            users_db[new_email] = users_db.pop(old_email)
            session['user_email'] = new_email
            flash('Email updated successfully')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/login.html -->
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h1>Login</h1>
    <form method="post">
        <label for="email">Email:</label>
        <input type="email" id="email" name="email" required><br>
        
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required><br>
        
        <button type="submit">Login</button>
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
    <meta charset="UTF-8">
    <title>Change Email</title>
</head>
<body>
    <h1>Change Email</h1>
    <form method="post">
        <label for="old_email">Old Email:</label>
        <input type="email" id="old_email" name="old_email" required><br>
        
        <label for="new_email">New Email:</label>
        <input type="email" id="new_email" name="new_email" required><br>
        
        <label for="confirm_password">Confirm Password:</label>
        <input type="password" id="confirm_password" name="confirm_password" required><br>
        
        <button type="submit">Change Email</button>
    </form>
    <a href="{{ url_for('logout') }}">Logout</a>
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