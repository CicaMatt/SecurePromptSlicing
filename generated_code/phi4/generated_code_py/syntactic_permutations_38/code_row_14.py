from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple user database for demonstration purposes.
USERS = {
    "user1": "password123",
    "admin": "adminpass"
}

LOGIN_PAGE = """
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
"""

DASHBOARD_PAGE = """
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<p>This is a protected area.</p>
<a href="{{ url_for('login') }}">Logout</a>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if USERS.get(username) == password:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login'))

    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    # In a real application, you would check session or token validity here
    return render_template_string(DASHBOARD_PAGE)

if __name__ == '__main__':
    app.run(debug=True)