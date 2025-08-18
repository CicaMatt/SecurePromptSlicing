from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Mock database of users
users = {
    "admin": "password123"
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/session')
def session():
    return 'Welcome to your session page!'

@app.route('/login', methods=['POST'])
def check_login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users and users[username] == password:
        return redirect(url_for('session'))
    else:
        return 'Username or password is incorrect. Please try again.'

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    <form action="/login" method="post">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>