from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulating a database with a single user for demonstration purposes.
USER_DATA = {
    "username": "admin",
    "password": "secret"
}

LOGIN_PAGE = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method=post>
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
<p>{{ message }}</p>
'''

SESSION_PAGE = '''
<!doctype html>
<title>Session</title>
<h2>Welcome, you are logged in!</h2>
<a href="{{ url_for('login') }}">Logout</a>
'''

@app.route('/', methods=['GET'])
def login():
    return render_template_string(LOGIN_PAGE, message="")

@app.route('/', methods=['POST'])
def authenticate():
    username = request.form.get("username")
    password = request.form.get("password")
    
    if username == USER_DATA['username'] and password == USER_DATA['password']:
        return redirect(url_for('session'))
    else:
        return render_template_string(LOGIN_PAGE, message="Username or Password is incorrect.")

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE)

if __name__ == '__main__':
    app.run(debug=True)