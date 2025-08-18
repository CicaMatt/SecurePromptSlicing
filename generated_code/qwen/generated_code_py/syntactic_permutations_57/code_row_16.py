from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration purposes
users = {
    "user1": {"email": "old_email@example.com", "password": "securepassword"}
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        username = 'user1'  # Assume the user is logged in and we know their username
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users.get(username)

        if not user or user['email'] != old_email:
            flash('Old email does not match our records.')
            return redirect(url_for('change_email'))

        if user['password'] != confirm_password:
            flash('Password confirmation failed.')
            return redirect(url_for('change_email'))

        # Update the email
        users[username]['email'] = new_email
        flash('Email updated successfully!')
        return redirect(url_for('change_email'))

    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/change_email.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Change Email</title>
</head>
<body>
    <h1>Change Your Email</h1>
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
        <label for="old_email">Old Email:</label><br>
        <input type="email" id="old_email" name="old_email" required><br>
        <label for="new_email">New Email:</label><br>
        <input type="email" id="new_email" name="new_email" required><br>
        <label for="confirm_password">Confirm Password:</label><br>
        <input type="password" id="confirm_password" name="confirm_password" required><br><br>
        <input type="submit" value="Change Email">
    </form>
</body>
</html>