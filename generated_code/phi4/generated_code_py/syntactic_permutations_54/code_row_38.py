from flask import Flask, render_template_string, request, redirect, url_for

app = Flask(__name__)

HTML_LOGIN_FORM = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form action="{{ url_for('do_login') }}" method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
'''

HTML_ADMIN_PAGE = '''
<!doctype html>
<title>Admin Page</title>
<h1>Welcome to the Admin Page!</h1>
<p>You have successfully logged in as an admin.</p>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(HTML_LOGIN_FORM)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    # Example check for admin credentials
    if username == 'admin' and password == 'secret':
        return redirect(url_for('admin_page'))
    else:
        return "Invalid login", 401

@app.route('/admin')
def admin_page():
    return render_template_string(HTML_ADMIN_PAGE)

if __name__ == '__main__':
    app.run(debug=True)