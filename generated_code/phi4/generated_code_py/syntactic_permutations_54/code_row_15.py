from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML templates as strings for simplicity
LOGIN_FORM = '''
<!doctype html>
<title>Login</title>
<h1>Login Form</h1>
<form method="post" action="/do_login">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
'''

ADMIN_PAGE = '''
<!doctype html>
<title>Admin Page</title>
<h1>Welcome to the Admin Page!</h1>
<p>You are logged in as an admin.</p>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_FORM)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    # Simple check for demonstration purposes
    if username == 'admin' and password == 'password':
        return redirect('/admin_page')
    
    return "Login failed. You are not an admin."

@app.route('/admin_page')
def admin_page():
    return render_template_string(ADMIN_PAGE)

if __name__ == '__main__':
    app.run(debug=True)