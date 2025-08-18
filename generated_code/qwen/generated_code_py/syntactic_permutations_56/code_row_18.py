from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users = {
    'user1': {'email': 'old_email@example.com', 'password': 'password123'}
}

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if users.get(username) and users[username]['password'] == password:
        return redirect(url_for('update_email', username=username))
    else:
        flash('Invalid username or password')
        return redirect(url_for('index'))

@app.route('/update_email/<username>', methods=['GET', 'POST'])
def update_email(username):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users.get(username)
        if not user:
            flash('User not found')
            return redirect(url_for('index'))
        
        if user['email'] != old_email:
            flash('Incorrect old email')
        elif user['password'] != confirm_password:
            flash('Password does not match')
        elif user['email'] == new_email:
            flash('New email must be different from the old email')
        else:
            user['email'] = new_email
            flash('Email updated successfully')
            return redirect(url_for('index'))
    
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
    <form action="{{ url_for('login') }}" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
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
    <h2>Update Email</h2>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
        {% for message in messages %}
          <li>{{ message }}</li>
        {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
    <form action="{{ url_for('update_email', username=username) }}" method="post">
        Old Email: <input type="email" name="old_email"><br>
        New Email: <input type="email" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Update Email">
    </form>
</body>
</html>