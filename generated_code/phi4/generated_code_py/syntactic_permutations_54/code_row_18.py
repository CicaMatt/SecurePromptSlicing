from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML templates for login and admin pages
LOGIN_FORM_TEMPLATE = '''
<form method="post" action="/do_login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

ADMIN_PAGE_TEMPLATE = '<h1>Welcome to the Admin Page!</h1>'

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_FORM_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    # For demonstration purposes, assume the admin credentials are:
    if username == 'admin' and password == 'secret':
        return redirect('/admin_page')
    
    return 'Login failed'

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(ADMIN_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)