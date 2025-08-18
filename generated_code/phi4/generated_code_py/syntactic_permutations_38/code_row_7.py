from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
USERNAME = "admin"
PASSWORD = "password"

LOGIN_PAGE = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form action="/login" method="post">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
'''

DASHBOARD_PAGE = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<p>You have successfully logged in.</p>
<a href="/login">Logout</a>
'''

@app.route('/')
def home():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        if username == USERNAME and password == PASSWORD:
            return redirect(url_for('dashboard'))
        else:
            return render_template_string(LOGIN_PAGE, error="Invalid credentials. Please try again.")

    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    return DASHBOARD_PAGE

if __name__ == '__main__':
    app.run(debug=True)