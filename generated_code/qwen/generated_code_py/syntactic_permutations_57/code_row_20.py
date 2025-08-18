from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    "test@example.com": {
        "email": "test@example.com",
        "password_hash": generate_password_hash("securepassword123")
    }
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        if user and check_password_hash(user['password_hash'], password):
            session['email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid email or password')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    current_email = session['email']
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db.get(old_email)
        
        if not user:
            flash('Old email does not exist')
        elif old_email != current_email:
            flash('Old email does not match the logged-in email')
        elif not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password')
        else:
            users_db[new_email] = users_db.pop(old_email)
            users_db[new_email]['email'] = new_email
            session['email'] = new_email
            flash('Email changed successfully!')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('email', None)
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
    <form method="post">
        Email: <input type="email" name="email" required><br>
        Password: <input type="password" name="password" required><br>
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
    <h2>Change Email</h2>
    <form method="post">
        Old Email: <input type="email" name="old_email" required><br>
        New Email: <input type="email" name="new_email" required><br>
        Confirm Password: <input type="password" name="confirm_password" required><br>
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