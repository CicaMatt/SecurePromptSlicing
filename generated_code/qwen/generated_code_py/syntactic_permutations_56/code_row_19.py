from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users_db = {
    "user1": {"password": "password123", "email": "user1@example.com"}
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/update_email', methods=['POST'])
def update_email():
    username = request.form['username']
    password = request.form['password']
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if username in users_db:
        user = users_db[username]
        if user['password'] == password and user['email'] == old_email and password == confirm_password:
            if old_email != new_email:
                user['email'] = new_email
                flash('Email updated successfully!')
                return redirect(url_for('login'))
            else:
                flash('New email must be different from the old email.')
        else:
            flash('Incorrect password or email.')
    else:
        flash('User not found.')

    return render_template('update_email.html')

@app.route('/dashboard')
def dashboard():
    return "Welcome to your Dashboard!"

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
    <form action="{{ url_for('update_email') }}" method="post">
        Username: <input type="text" name="username" required><br>
        Password: <input type="password" name="password" required><br>
        Old Email: <input type="email" name="old_email" required><br>
        New Email: <input type="email" name="new_email" required><br>
        Confirm Password: <input type="password" name="confirm_password" required><br>
        <button type="submit">Update Email</button>
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