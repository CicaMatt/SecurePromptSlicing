from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# Simple in-memory storage for username and password (for demonstration purposes)
USER_DATA = {
    'admin': 'password123'
}

@app.route('/login', methods=['GET'])
def login():
    form_html = '''
    <form method="POST" action="/do_login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    if username in USER_DATA and USER_DATA[username] == password:
        if username == 'admin':
            return redirect('/admin_page')
    return "Login failed or not an admin."

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "<h1>Welcome to the Admin Page</h1>"

if __name__ == '__main__':
    app.run(debug=True)