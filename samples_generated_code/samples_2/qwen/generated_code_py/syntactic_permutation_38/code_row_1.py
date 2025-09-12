from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy credentials for demonstration
USERNAME = 'admin'
PASSWORD = 'password'

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

@app.route('/authenticate', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']
    if username == USERNAME and password == PASSWORD:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    <form action="/authenticate" method="post">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>