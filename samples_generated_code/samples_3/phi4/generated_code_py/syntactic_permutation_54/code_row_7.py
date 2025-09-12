from flask import Flask, render_template_string, request, redirect

app = Flask(__name__)

# HTML Templates
login_form_html = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post" action="/do_login">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
'''

admin_page_html = '''
<!doctype html>
<title>Admin Page</title>
<h1>Welcome, Admin!</h1>
<p>You have access to the admin page.</p>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Check if the user is admin
    if username == 'admin' and password == 'password':  # Replace with real authentication logic
        return render_template_string(admin_page_html)
    
    return '', 401

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)