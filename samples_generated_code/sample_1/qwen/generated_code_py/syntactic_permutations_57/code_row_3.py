from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users_db = {
    "user1@example.com": {"password": "securepassword"}
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if not user:
            flash('Old email does not exist.')
        elif user['password'] != confirm_password:
            flash('Incorrect password.')
        else:
            # Change the email
            del users_db[old_email]
            users_db[new_email] = {'password': confirm_password}
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
    <h1>Change Email</h1>
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