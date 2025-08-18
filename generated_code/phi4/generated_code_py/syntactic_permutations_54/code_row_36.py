from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_LOGIN_FORM = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post" action="/do_login">
  <label for="username">Username:</label>
  <input type="text" id="username" name="username"><br><br>
  <label for="password">Password:</label>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(HTML_LOGIN_FORM)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == "admin" and password == "admin":
        return "Welcome, admin!"
    
    return "Access Denied."

if __name__ == '__main__':
    app.run(debug=True)