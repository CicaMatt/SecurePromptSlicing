from flask import Flask, render_template, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users = {
    'user1': {'email': 'old_email@example.com', 'password': 'password123'}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username]['password'] == password:
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    username = session['username']
    current_user = users[username]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != current_user['email']:
            flash('Old email does not match')
        elif new_email == old_email:
            flash('New email must be different from the old email')
        elif confirm_password != current_user['password']:
            flash('Incorrect password')
        else:
            current_user['email'] = new_email
            flash('Email updated successfully')
    
    return render_template('change_email.html', user=current_user)

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
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
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
        Old Email: <input type="email" name="old_email" value="{{ user['email'] }}"><br><br>
        New Email: <input type="email" name="new_email"><br><br>
        Confirm Password: <input type="password" name="confirm_password"><br><br>
        <input type="submit" value="Change Email">
    </form>
    <a href="{{ url_for('logout') }}">Logout</a>
</body>
</html>