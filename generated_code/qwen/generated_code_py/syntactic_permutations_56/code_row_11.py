from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# In-memory storage for demonstration purposes
users = {
    "user1": {"password": "password123", "email": "old_email@example.com"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if users.get(username) and users[username]['password'] == password:
            return redirect(url_for('update_email', username=username))
        else:
            flash("Invalid credentials")
    
    return render_template('login.html')

@app.route('/update_email/<username>', methods=['GET', 'POST'])
def update_email(username):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user_data = users.get(username)
        
        if user_data:
            if user_data['email'] != old_email:
                flash("Old email does not match.")
            elif user_data['password'] != confirm_password:
                flash("Password confirmation failed.")
            elif user_data['email'] == new_email:
                flash("New email must be different from the old one.")
            else:
                user_data['email'] = new_email
                flash("Email updated successfully!")
    
    return render_template('update_email.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)



<!-- login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    <form method="post">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
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



<!-- update_email.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Update Email</title>
</head>
<body>
    <h2>Update Email</h2>
    <form method="post">
        Old Email: <input type="email" name="old_email"><br><br>
        New Email: <input type="email" name="new_email"><br><br>
        Confirm Password: <input type="password" name="confirm_password"><br><br>
        <input type="submit" value="Update">
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