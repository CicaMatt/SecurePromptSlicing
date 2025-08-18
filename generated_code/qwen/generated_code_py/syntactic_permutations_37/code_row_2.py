from flask import Flask, request, redirect, url_for, render_template

app = Flask(__name__)

# Mock database of users
users_db = {
    "admin": "password123",
    "user": "mypassword"
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form.get('username')
    password = request.form.get('password')
    
    try:
        if username in users_db and users_db[username] == password:
            return redirect(url_for('success'))
        else:
            return redirect(url_for('cant_login'))
    except Exception as e:
        return redirect(url_for('internal_server_error'))

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Log In"

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

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
    <h2>Login</h2>
    <form action="{{ url_for('authenticate') }}" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>