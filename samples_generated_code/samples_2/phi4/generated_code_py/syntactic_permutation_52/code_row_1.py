from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# HTML templates
index_html = """
<!doctype html>
<html lang="en">
  <body>
    <h1>Welcome to the index page!</h1>
    <a href="{{ url_for('login') }}">Login</a>
  </body>
</html>
"""

login_html = """
<!doctype html>
<html lang="en">
  <body>
    <h1>Login Page</h1>
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

secret_html = """
<!doctype html>
<html lang="en">
  <body>
    <h1>Secret settings</h1>
  </body>
</html>
"""

# User credentials for demonstration
VALID_USERNAME = 'admin'
VALID_PASSWORD = 'password'

@app.route('/')
def index():
    return render_template_string(index_html)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if do_login(username, password):
            return redirect(url_for('secret'))
    
    return render_template_string(login_html)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    return render_template_string(secret_html)

def do_login(username, password):
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        session['username'] = username
        return True
    return False

if __name__ == '__main__':
    app.run(debug=True)