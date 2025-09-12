from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database of users
users_db = {
    "admin": "password123"
}

login_page_html = """
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h1>Login</h1>
    <form action="/login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

dashboard_page_html = """
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Dashboard</title>
</head>
<body>
    <h1>Welcome to the Dashboard</h1>
    <a href="/logout">Logout</a>
</body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']
    
    if users_db.get(username) == password:
        return redirect('/dashboard')
    else:
        return redirect('/')

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page_html)

@app.route('/logout')
def logout():
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)