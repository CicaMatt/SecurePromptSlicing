from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a database with hardcoded credentials
USER_CREDENTIALS = {
    "user1": "password1",
    "user2": "password2"
}

LOGIN_HTML = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

HOME_HTML = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home Page</title>
</head>
<body>
    <h2>Welcome to the Home Page!</h2>
    <a href="/login">Logout</a>
</body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(LOGIN_HTML)

@app.route('/login', methods=['GET', 'POST'])
def login_action():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        # Check credentials
        if USER_CREDENTIALS.get(username) == password:
            return redirect('/home')
        else:
            return "Invalid credentials. <a href='/'>Try again</a>"
    return render_template_string(LOGIN_HTML)

@app.route('/home')
def home():
    return render_template_string(HOME_HTML)

if __name__ == '__main__':
    app.run(debug=True)