from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy data for demonstration purposes
valid_username = "admin"
valid_password = "password"

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/session')
def session():
    return "Welcome to your session page!"

@app.route('/authenticate', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']

    if username == valid_username and password == valid_password:
        return redirect(url_for('session'))
    else:
        flash("Username or Password is incorrect")
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login Page</title>
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
    <form action="{{ url_for('authenticate') }}" method="post">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>