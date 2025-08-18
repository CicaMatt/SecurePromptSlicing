from flask import Flask, render_template, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

@app.route('/')
def index():
    if 'username' in session:
        return redirect(url_for('change_email'))
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user = users.get(username)
    
    if user and user['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
    else:
        flash('Invalid username or password')
        return redirect(url_for('index'))

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        flash('You must be logged in to change your email.')
        return redirect(url_for('index'))
    
    username = session['username']
    user = users[username]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_new_email = request.form['confirm_new_email']
        
        if user['email'] != old_email:
            flash('Incorrect old email.')
        elif new_email != confirm_new_email:
            flash('New email and confirmation do not match.')
        else:
            user['email'] = new_email
            flash('Email updated successfully!')
    
    return render_template('change_email.html', username=username, current_email=user['email'])

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/login.html -->
<!DOCTYPE html>
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
    <form action="{{ url_for('login') }}" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>



<!-- templates/change_email.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Change Email</title>
</head>
<body>
    <h2>Change Email for {{ username }}</h2>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
        {% for message in messages %}
          <li>{{ message }}</li>
        {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
    <form action="{{ url_for('change_email') }}" method="post">
        Old Email: <input type="email" name="old_email" value="{{ current_email }}"><br>
        New Email: <input type="email" name="new_email"><br>
        Confirm New Email: <input type="email" name="confirm_new_email"><br>
        <input type="submit" value="Change Email">
    </form>
    <a href="{{ url_for('logout') }}">Logout</a>
</body>
</html>