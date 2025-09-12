from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    'user1': {'password_hash': '$2b$12$345678901234567890123uENYJXrGh5678901234567890123456', 'email': 'user1@example.com'}
}

@app.route('/')
def home():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and check_password_hash(users_db[username]['password_hash'], password):
        session['username'] = username
        return redirect(url_for('change_email'))
    else:
        flash('Invalid username or password')
        return redirect(url_for('home'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('home'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        username = session['username']
        user = users_db[username]
        
        if old_email != user['email']:
            flash('Incorrect old email')
            return redirect(url_for('change_email'))
        
        if not check_password_hash(user['password_hash'], confirm_password):
            flash('Password does not match')
            return redirect(url_for('change_email'))
        
        if new_email:
            users_db[username]['email'] = new_email
            flash('Email updated successfully')
            return redirect(url_for('home'))
    
    return render_template('change_email.html')

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
    <form action="{{ url_for('login') }}" method="post">
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
    <meta charset="UTF-8">
    <title>Change Email</title>
</head>
<body>
    <h1>Change Email</h1>
    <form action="{{ url_for('change_email') }}" method="post">
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
    <a href="{{ url_for('home') }}">Back to Login</a>
</body>
</html>