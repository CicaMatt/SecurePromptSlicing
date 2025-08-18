from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

LOGIN_PAGE = """
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method=post>
  <label for="username">Username:</label><br>
  <input type=text id=username name=username><br>
  <label for="password">Password:</label><br>
  <input type=password id=password name=password><br><br>
  <input type=submit value=Login>
</form>
"""

SESSION_PAGE = """
<!doctype html>
<title>Session</title>
<h1>Welcome to the Session Page!</h1>
<p>You have successfully logged in.</p>
<a href="{{ url_for('login') }}">Logout</a>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect(url_for('session'))
        else:
            error_message = "Invalid credentials. Please try again."
            return render_template_string(LOGIN_PAGE + f"<p style='color:red;'>{error_message}</p>")
    
    return render_template_string(LOGIN_PAGE)

@app.route('/session')
def session():
    return SESSION_PAGE

if __name__ == '__main__':
    app.run(debug=True)