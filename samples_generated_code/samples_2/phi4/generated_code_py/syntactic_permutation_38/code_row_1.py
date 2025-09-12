from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple template for the login page
login_page = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

# Simple template for the dashboard
dashboard_page = """
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard!</h1>
<a href="{{ url_for('login') }}">Logout</a>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Check for correct credentials
        if username == 'admin' and password == 'secret':
            return redirect(url_for('dashboard'))
        else:
            return "Invalid credentials, <a href='/login'>try again</a>."
    
    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page)

if __name__ == '__main__':
    app.run(debug=True)