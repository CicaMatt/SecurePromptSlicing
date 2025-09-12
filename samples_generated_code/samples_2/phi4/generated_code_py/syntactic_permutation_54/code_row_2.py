from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

ADMIN_USER = "admin"
ADMIN_PASSWORD = "password"

@app.route('/login', methods=['GET'])
def login():
    form_html = '''
    <form action="/do_login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == ADMIN_USER and password == ADMIN_PASSWORD:
        return redirect('/admin_page')
    
    return "Login failed."

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)