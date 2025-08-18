from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

LOGIN_FORM = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form action="/do_login" method="post">
  <label for="username">Username:</label>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_FORM)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Here we would normally check the credentials against a database or authentication service.
    if username == 'admin' and password == 'password':
        return redirect('/')
    
    return "Login Failed", 401

if __name__ == '__main__':
    app.run(debug=True)