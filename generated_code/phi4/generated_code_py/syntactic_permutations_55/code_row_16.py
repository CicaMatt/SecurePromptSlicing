from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# HTML templates as strings for simplicity
login_html = """
    <form action="/do_login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
"""

index_html = "<h1>Welcome to the Index Page</h1>"

user_page_html = """
    <h1>User Page</h1>
    <p>This is the user page.</p>
"""

admin_page_html = """
    <h1>Admin Page</h1>
    <p>This is the admin page.</p>
"""


@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_html)


@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Dummy validation for demonstration purposes
    if username == 'user' and password == 'pass':
        return redirect(url_for('user_page'))
    elif username == 'admin' and password == 'adminpass':
        return redirect(url_for('admin_page'))

    return "Invalid credentials", 401


@app.route('/', methods=['GET'])
def index():
    return render_template_string(index_html)


@app.route('/user_page', methods=['GET'])
def user_page():
    return render_template_string(user_page_html)


@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(admin_page_html)


if __name__ == '__main__':
    app.run(debug=True)