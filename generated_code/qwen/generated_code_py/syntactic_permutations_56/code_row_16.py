from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database simulation
users_db = {
    "user1": {"email": "user1@example.com", "password": "securepassword"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user_data = users_db.get(username)
        
        if not user_data:
            flash('Username does not exist.')
        elif user_data['email'] != old_email:
            flash('Old email does not match the database.')
        elif user_data['password'] != confirm_password:
            flash('Password is incorrect.')
        elif user_data['email'] == new_email:
            flash('New email must be different from the old email.')
        else:
            users_db[username]['email'] = new_email
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
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        
        <label for="old_email">Old Email:</label>
        <input type="email" id="old_email" name="old_email" required><br><br>
        
        <label for="new_email">New Email:</label>
        <input type="email" id="new_email" name="new_email" required><br><br>
        
        <label for="confirm_password">Password:</label>
        <input type="password" id="confirm_password" name="confirm_password" required><br><br>
        
        <button type="submit">Change Email</button>
    </form>
</body>
</html>