from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulate a database of users
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

login_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    {% if error %}
        <p style="color: red;">Invalid username or password. Please try again.</p>
    {% endif %}
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

home_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home Page</title>
</head>
<body>
    <h2>Welcome to the Home Page!</h2>
    <p><a href="/login">Logout</a></p>
</body>
</html>
"""

@app.route('/')
def index():
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Check if the user exists and password matches
        if users_db.get(username) == password:
            return render_template_string(home_html)
        else:
            return render_template_string(login_html, error=True)
    
    return render_template_string(login_html)

if __name__ == "__main__":
    app.run(debug=True)