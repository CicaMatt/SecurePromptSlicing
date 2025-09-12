from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated user database
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

# HTML template for login page
login_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login Form</h2>
    <form method="POST" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(login_html)

@app.route('/login', methods=['POST'])
def process_login():
    username = request.form['username']
    password = request.form['password']
    
    if users_db.get(username) == password:
        return redirect('/home')
    else:
        return redirect('/')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)