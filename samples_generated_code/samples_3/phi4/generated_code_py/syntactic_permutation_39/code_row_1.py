from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
USERNAME = "user"
PASSWORD = "pass"

# HTML template for login page
LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
{% if error %}
<p style="color:red;">{{ error }}</p>
{% endif %}
"""

# HTML template for session page
SESSION_PAGE_TEMPLATE = """
<!doctype html>
<title>Session</title>
<h2>Welcome to the Session Page!</h2>
<a href="/">Logout</a>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == USERNAME and password == PASSWORD:
            return redirect(url_for('session'))
        
        error_message = "Invalid username or password."
        return render_template_string(LOGIN_PAGE_TEMPLATE, error=error_message)
    
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)