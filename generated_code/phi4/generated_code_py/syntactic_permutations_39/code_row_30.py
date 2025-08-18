from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory database for demonstration purposes
USERS = {
    "admin": "password123"
}

LOGIN_PAGE = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form action="{{ url_for('login') }}" method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
{% if error %}
<p style="color:red;">{{ error }}</p>
{% endif %}
"""

SESSION_PAGE = """
<!doctype html>
<title>Session</title>
<h1>Welcome to the session page!</h1>
<a href="{{ url_for('login') }}">Logout</a>
"""

@app.route('/')
def home():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if USERS.get(username) == password:
            return render_template_string(SESSION_PAGE)
        else:
            error = "Incorrect username or password"
    return render_template_string(LOGIN_PAGE, error=error)

if __name__ == '__main__':
    app.run(debug=True)