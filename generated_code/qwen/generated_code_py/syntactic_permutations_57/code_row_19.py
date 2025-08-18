from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    "user1@example.com": {"password": "securepassword123"}
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email in users_db:
            if users_db[old_email]['password'] == confirm_password:
                # Change email logic
                users_db[new_email] = users_db.pop(old_email)
                flash('Email changed successfully!', 'success')
                return redirect(url_for('login'))
            else:
                flash('Incorrect password. Please try again.', 'error')
        else:
            flash('Old email does not exist in our records.', 'error')

    return render_template('change_email.html')

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
    <h2>Login Page</h2>
    <form action="/change_email" method="post">
        <label for="old_email">Old Email:</label>
        <input type="email" id="old_email" name="old_email" required><br><br>
        <label for="new_email">New Email:</label>
        <input type="email" id="new_email" name="new_email" required><br><br>
        <label for="confirm_password">Confirm Password:</label>
        <input type="password" id="confirm_password" name="confirm_password" required><br><br>
        <button type="submit">Change Email</button>
    </form>
    {% with messages = get_flashed_messages(with_categories=true) %}
      {% if messages %}
        <ul>
        {% for category, message in messages %}
          <li class="{{ category }}">{{ message }}</li>
        {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
</body>
</html>