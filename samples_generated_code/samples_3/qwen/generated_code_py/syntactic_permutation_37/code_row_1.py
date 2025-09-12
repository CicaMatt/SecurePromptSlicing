from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "admin": "password123",
    "user": "secret"
}

login_form = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

@app.route('/')
def home():
    return render_template_string(login_form)

@app.route('/login', methods=['POST'])
def login():
    try:
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return redirect('/success')
        else:
            return redirect('/cant_login')
    except Exception as e:
        return redirect('/internal_server_error')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot log in. Please check your username and password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)