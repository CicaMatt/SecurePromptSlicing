from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users_db = {
    "user1": {"email": "old_email@example.com", "password": "secure_password"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_new_email = request.form['confirm_new_email']
        password = request.form['password']

        user = users_db.get(username)
        if user and user["email"] == old_email and user["password"] == password:
            if new_email != old_email:
                if new_email == confirm_new_email:
                    user["email"] = new_email
                    flash('Email updated successfully!')
                    return redirect(url_for('login'))
                else:
                    flash('New email and confirm email do not match.')
            else:
                flash('New email must be different from the old email.')
        else:
            flash('Invalid username, password, or old email.')

    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- login.html -->
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
    <form method="post" action="">
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