from flask import Flask, request, redirect, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database for demonstration purposes
users_db = {
    "user1": "password1",
    "user2": "password2"
}

login_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form> 
  </body>
</html>
'''

home_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Home Page</title>
  </head>
  <body>
    <h1>Welcome to the Home Page!</h1>
    <p>You are logged in as {{ username }}.</p>
    <a href="/logout">Logout</a>
  </body>
</html>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if users_db.get(username) == password:
            session['username'] = username
            return redirect('/home')
        else:
            return redirect('/')
    
    return render_template_string(login_html)

@app.route('/home')
def home():
    if 'username' not in session:
        return redirect('/')
    return render_template_string(home_html, username=session['username'])

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect('/')

@app.route('/')
def index():
    return render_template_string(login_html)

if __name__ == '__main__':
    app.run(debug=True)