from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for simplicity
USERNAME = "user"
PASSWORD = "pass"

LOGIN_PAGE = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
{% if error %}
<p style="color: red;">{{ error }}</p>
{% endif %}
'''

SESSION_PAGE = '''
<!doctype html>
<title>Session Page</title>
<h2>Welcome!</h2>
<p>You have successfully logged in.</p>
<a href="{{ url_for('login') }}">Logout and go back to login page</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == USERNAME and password == PASSWORD:
            return redirect(url_for('session'))
        else:
            error = "Username or Password is incorrect"
    return render_template_string(LOGIN_PAGE, error=error)

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE)

if __name__ == '__main__':
    app.run(debug=True)