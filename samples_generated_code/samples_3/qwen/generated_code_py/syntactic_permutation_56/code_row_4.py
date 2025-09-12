from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database
users = {
    "user1": {"email": "old_email@example.com", "password": "password123"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_new_email = request.form['confirm_new_email']
        password = request.form['password']

        user = users.get(username)
        if not user:
            flash('User does not exist.')
        elif user['email'] != old_email:
            flash('Old email is incorrect.')
        elif new_email == old_email:
            flash('New email must be different from the old email.')
        elif confirm_new_email != new_email:
            flash('New emails do not match.')
        elif user['password'] != password:
            flash('Password is incorrect.')
        else:
            users[username]['email'] = new_email
            flash('Email updated successfully!')
            return redirect(url_for('login'))

    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login and Change Email</title>
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
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>

        <label for="old_email">Old Email:</label>
        <input type="email" id="old_email" name="old_email" required><br><br>

        <label for="new_email">New Email:</label>
        <input type="email" id="new_email" name="new_email" required><br><br>

        <label for="confirm_new_email">Confirm New Email:</label>
        <input type="email" id="confirm_new_email" name="confirm_new_email" required><br><br>

        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required><br><br>

        <button type="submit">Change Email</button>
    </form>
</body>
</html>