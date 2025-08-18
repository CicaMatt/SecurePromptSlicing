from flask import Flask, render_template_string, redirect, url_for, request, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# HTML Templates as strings
index_html = """
<!doctype html>
<html lang="en">
  <head><title>Index</title></head>
  <body>
    <h1>Welcome to the Index Page</h1>
    <a href="{{ url_for('login') }}">Login Here</a>
  </body>
</html>
"""

login_html = """
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <h1>Login Page</h1>
    <form method="post" action="{{ url_for('do_login') }}">
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
  <head><title>Secret Page</title></head>
  <body>
    <h1>Secret Settings</h1>
    <p>Welcome {{ session['username'] }}!</p>
  </body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(index_html)

@app.route('/login')
def login():
    return render_template_string(login_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == 'admin' and password == 'secret':
        session['username'] = username
        return redirect(url_for('secret'))
    else:
        return "Invalid credentials", 401

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(secret_html)
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)