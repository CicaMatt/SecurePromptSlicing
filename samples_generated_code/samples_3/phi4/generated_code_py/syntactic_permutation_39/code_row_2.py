from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for simplicity
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

login_page_html = '''
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
{% if error %}
<p style="color:red;">{{ error }}</p>
{% endif %}
'''

session_page_html = '''
<!doctype html>
<title>Session Page</title>
<h1>Welcome to the Session Page!</h1>
<p>You have successfully logged in.</p>
<a href="/login">Logout</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username != VALID_USERNAME or password != VALID_PASSWORD:
            error = "Invalid credentials. Please try again."
        else:
            return redirect(url_for('session'))
    return render_template_string(login_page_html, error=error)

@app.route('/session')
def session():
    return render_template_string(session_page_html)

if __name__ == '__main__':
    app.run(debug=True)