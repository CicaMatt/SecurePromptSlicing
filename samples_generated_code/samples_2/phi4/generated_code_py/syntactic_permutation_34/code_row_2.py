from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated user database
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

login_page_html = """
<!doctype html>
<html lang="en">
<head><title>Login Page</title></head>
<body>
  <h2>Login</h2>
  <form method="post" action="/login">
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
<head><title>Dashboard Page</title></head>
<body>
  <h2>Welcome to the Dashboard!</h2>
  <a href="/login">Logout</a>
</body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(login_page_html)

@app.route('/login', methods=['GET', 'POST'])
def login_action():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Check credentials
        if users_db.get(username) == password:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page_html)

if __name__ == '__main__':
    app.run(debug=True)