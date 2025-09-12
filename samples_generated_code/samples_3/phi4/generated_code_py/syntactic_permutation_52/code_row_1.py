from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

USER_CREDENTIALS = {'admin': 'password123'}

LOGIN_PAGE_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <h2>Login</h2>
    <form method="POST" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

INDEX_PAGE_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head><title>Index</title></head>
  <body>
    <h2>Welcome to the Index Page</h2>
    <a href="/login">Go to Login</a>
  </body>
</html>
'''

SECRET_PAGE_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head><title>Secret Settings</title></head>
  <body>
    <h1>Secret settings</h1>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE_TEMPLATE)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username in USER_CREDENTIALS and USER_CREDENTIALS[username] == password:
            session['username'] = username
            return redirect(url_for('secret'))
        
        return "Invalid credentials", 401

    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))

    return render_template_string(SECRET_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)