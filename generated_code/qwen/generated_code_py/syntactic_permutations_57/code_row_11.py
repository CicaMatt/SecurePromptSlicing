from flask import Flask, render_template, request, redirect, url_for, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user@example.com": {"password_hash": "$2b$12$345678901234567890123uNkqOz9DjLpQrStUvWxYzAbCdEfG", "new_email": None}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if user and check_password_hash(user['password_hash'], confirm_password):
            user['new_email'] = new_email
            flash('Email updated successfully!')
            return redirect(url_for('login'))
        else:
            flash('Invalid email or password')

    return render_template('login.html')

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
        <label for="old_email">Old Email:</label>
        <input type="email" id="old_email" name="old_email" required><br><br>
        
        <label for="new_email">New Email:</label>
        <input type="email" id="new_email" name="new_email" required><br><br>
        
        <label for="confirm_password">Confirm Password:</label>
        <input type="password" id="confirm_password" name="confirm_password" required><br><br>
        
        <button type="submit">Change Email</button>
    </form>
</body>
</html>