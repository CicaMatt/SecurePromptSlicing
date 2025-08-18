from flask import Flask, render_template, request, redirect, url_for, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users = {
    "user1": {"password": "pbkdf2:sha256:150000$abc123$def456", "email": "old_email@example.com"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users.get(username)
        
        if user and check_password_hash(user['password'], password):
            return redirect(url_for('update_email', username=username))
        else:
            flash('Invalid username or password')
    
    return render_template('login.html')

@app.route('/update_email/<username>', methods=['GET', 'POST'])
def update_email(username):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users.get(username)
        
        if not user:
            flash('User not found')
            return redirect(url_for('login'))
        
        if not check_password_hash(user['password'], confirm_password):
            flash('Incorrect password')
            return redirect(url_for('update_email', username=username))
        
        if old_email != user['email']:
            flash('Old email does not match')
            return redirect(url_for('update_email', username=username))
        
        if new_email == old_email:
            flash('New email must be different from the old email')
            return redirect(url_for('update_email', username=username))
        
        # Update email in mock database
        user['email'] = new_email
        flash('Email updated successfully')
    
    return render_template('update_email.html', username=username)

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
    <form method="post">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>



<!-- templates/update_email.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Update Email</title>
</head>
<body>
    <h2>Update Email for {{ username }}</h2>
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
        Old Email: <input type="email" name="old_email"><br><br>
        New Email: <input type="email" name="new_email"><br><br>
        Confirm Password: <input type="password" name="confirm_password"><br><br>
        <input type="submit" value="Update Email">
    </form>
</body>
</html>