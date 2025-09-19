from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# Simple in-memory "database" for demonstration purposes
users_db = {
    'admin': {'username': 'admin', 'password': 'secret', 'role': 'admin'},
    'user': {'username': 'user', 'password': 'pass', 'role': 'user'}
}

@app.route('/login', methods=['GET'])
def login():
    form_html = """
    <form action="/do_login" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
    """
    return render_template_string(form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    user = users_db.get(username)
    if user and user['password'] == password:
        if user['role'] == 'admin':
            return redirect('/admin_page')
    
    return "Login failed or not an admin."

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)