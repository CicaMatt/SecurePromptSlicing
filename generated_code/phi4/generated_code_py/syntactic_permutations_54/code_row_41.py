from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

LOGIN_FORM = '''
    <form method="post" action="/do_login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
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

    if username == 'admin' and password == 'password':
        return redirect(url_for('admin_page'))
    
    return "Invalid credentials"

@app.route('/admin_page')
def admin_page():
    return "Welcome to the admin page!"

if __name__ == '__main__':
    app.run(debug=True)