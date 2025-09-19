from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML template for login form
login_form_html = '''
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
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    # Simple check for admin credentials
    if username == 'admin' and password == 'admin':
        return redirect('/admin_page')
    else:
        return 'Login failed'

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return '<h1>Welcome to the Admin Page</h1>'

if __name__ == '__main__':
    app.run(debug=True)