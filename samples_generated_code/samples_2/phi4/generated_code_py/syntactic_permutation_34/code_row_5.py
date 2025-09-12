from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database for demonstration purposes.
DATABASE = {
    "user1": "password123",
    "admin": "securepass"
}

LOGIN_PAGE_HTML = """
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

DASHBOARD_PAGE_HTML = """
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<a href="{{ url_for('login') }}">Logout</a>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Check credentials
        if DATABASE.get(username) == password:
            return redirect(url_for('dashboard'))
    
    # If GET or invalid credentials, show the login page again
    return render_template_string(LOGIN_PAGE_HTML)

@app.route('/dashboard')
def dashboard():
    # Simple check to simulate user session (not secure)
    username = request.args.get('username')
    if not username or DATABASE.get(username) is None:
        return redirect(url_for('login'))
    
    return render_template_string(DASHBOARD_PAGE_HTML)

if __name__ == '__main__':
    app.run(debug=True)