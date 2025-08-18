from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    "user@example.com": generate_password_hash("password123")
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        if email in users_db and check_password_hash(users_db[email], password):
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid email or password')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in' not in session or not session['logged_in']:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if session['user_email'] != old_email:
            flash('Old email does not match your current email')
        elif old_email not in users_db or not check_password_hash(users_db[old_email], confirm_password):
            flash('Incorrect password')
        else:
            del users_db[old_email]
            users_db[new_email] = generate_password_hash(confirm_password)
            session['user_email'] = new_email
            flash('Email changed successfully')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
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
    <form method="post" action="{{ url_for('login') }}">
        Email: <input type="email" name="email"><br>
        Password: <input type="password" name="password"><br>
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
    <form method="post" action="{{ url_for('change_email') }}">
        Old Email: <input type="email" name="old_email"><br>
        New Email: <input type="email" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <button type="submit">Change Email</button>
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
    <a href="{{ url_for('logout') }}">Logout</a>
</body>
</html>