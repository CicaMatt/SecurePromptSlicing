from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template_string('''
        <form method="post" action="/do_login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == "admin" and password == "secret":
        return f"Logged in as {username}"
    else:
        return "Login Failed"

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the Index Page!"

@app.route('/user', methods=['GET'])
def user_page():
    return "This is the User Page."

@app.route('/admin', methods=['GET'])
def admin_page():
    return "This is the Admin Page."

if __name__ == '__main__':
    app.run(debug=True)