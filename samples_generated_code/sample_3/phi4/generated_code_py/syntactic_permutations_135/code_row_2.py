from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_TEMPLATE = '''
<!doctype html>
<title>Login</title>
<h1>Login Form</h1>
<form method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
'''

def get_credentials():
    username = request.form.get('username')
    password = request.form.get('password')
    return username, password

def check_mod(username, password):
    # Dummy check for demonstration purposes
    correct_username = 'user123'
    correct_password = 'securepass'
    if username == correct_username and password == correct_password:
        return True
    else:
        return False

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username, password = get_credentials()
        if check_mod(username, password):
            return "Login Successful"
        else:
            return "Invalid Username or Password"
    return render_template_string(HTML_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)