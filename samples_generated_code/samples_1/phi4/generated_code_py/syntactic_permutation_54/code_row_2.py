from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

ADMIN_USERNAME = "admin"
ADMIN_PASSWORD = "password"

def login():
    form_html = '''
    <form method="post" action="/do_login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(form_html)

def admin_page():
    return "Welcome to the Admin Page!"

@app.route('/login', methods=['GET'])
def login_view():
    return login()

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == ADMIN_USERNAME and password == ADMIN_PASSWORD:
        return redirect('/admin_page')
    else:
        return "Invalid credentials or not an admin."

@app.route('/admin_page')
def admin_view():
    return admin_page()

if __name__ == '__main__':
    app.run(debug=True)