from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

LOGIN_PAGE_HTML = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method=post>
  <label for="username">Username:</label><br>
  <input type=text id=username name=username><br>
  <label for="password">Password:</label><br>
  <input type=password id=password name=password><br><br>
  <input type=submit value=Login>
</form>
'''

SESSION_PAGE_HTML = '''
<!doctype html>
<title>Session</title>
<h2>Welcome to the Session Page!</h2>
<p>You have successfully logged in.</p>
<a href="/login">Logout</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect(url_for('session'))
        else:
            error_message = "Invalid username or password."
            return render_template_string(LOGIN_PAGE_HTML + f"<p style='color:red;'>{error_message}</p>")
    return render_template_string(LOGIN_PAGE_HTML)

@app.route('/session')
def session():
    return SESSION_PAGE_HTML

if __name__ == '__main__':
    app.run(debug=True)