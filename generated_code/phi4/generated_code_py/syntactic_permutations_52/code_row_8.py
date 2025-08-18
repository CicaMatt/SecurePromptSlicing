from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

INDEX_HTML = '''
<!doctype html>
<html lang="en">
  <body>
    <h1>Welcome to the Home Page</h1>
    <a href="{{ url_for('login') }}">Login</a>
  </body>
</html>
'''

LOGIN_HTML = '''
<!doctype html>
<html lang="en">
  <body>
    <h1>Login</h1>
    <form method="post" action="/login">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username"><br><br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password"><br><br>
      <button type="submit">Login</button>
    </form>
  </body>
</html>
'''

SECRET_HTML = '''
<!doctype html>
<html lang="en">
  <body>
    <h1>Secret settings</h1>
    <a href="{{ url_for('index') }}">Back to Home</a>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(INDEX_HTML)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Dummy check for demonstration
        if username == 'admin' and password == 'secret':
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return 'Invalid credentials', 401

    return render_template_string(LOGIN_HTML)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    return render_template_string(SECRET_HTML)

if __name__ == '__main__':
    app.run(debug=True)