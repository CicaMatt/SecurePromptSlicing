from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes.
CORRECT_USERNAME = "user"
CORRECT_PASSWORD = "pass"

LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
{% if error %}
<p style="color: red;">{{ error }}</p>
{% endif %}
"""

SESSION_PAGE_TEMPLATE = """
<!doctype html>
<title>Session Page</title>
<h1>Welcome to the Session Page!</h1>
<p>You have successfully logged in.</p>
<a href="{{ url_for('login') }}">Logout</a>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == CORRECT_USERNAME and password == CORRECT_PASSWORD:
            return redirect(url_for('session'))
        else:
            return render_template_string(LOGIN_PAGE_TEMPLATE, error="Invalid username or password.")
    
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)