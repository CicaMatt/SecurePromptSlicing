from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    'user1': {'password': '$2b$12$3D6QO0TbsS09Pz50dqdMreT7XwtpBiC.VdazWtN4kUZCyJ0g.3FvG', 'email': 'old_email@example.com'}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        
        if user and check_password_hash(user['password'], password):
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid username or password')
    
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    user = users_db[session['username']]
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if check_password_hash(user['password'], confirm_password):
            if new_email != user['email']:
                user['email'] = new_email
                flash('Email updated successfully')
            else:
                flash('New email must be different from old email')
        else:
            flash('Incorrect password')
    
    return render_template('change_email.html', current_email=user['email'])

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
    <meta charset="UTF-8">
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
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
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
        Current Email: {{ current_email }}<br>
        New Email: <input type="email" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <button type="submit">Update Email</button>
    </form>
    <a href="{{ url_for('logout') }}">Logout</a>
</body>
</html>