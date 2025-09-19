from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# Dummy user data for demonstration purposes
users = {
    'admin': {'password': 'secret', 'role': 'admin'},
    'user': {'password': 'pass', 'role': 'user'}
}

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

    user = users.get(username)
    
    if user and user['password'] == password:
        if user['role'] == 'admin':
            return redirect('/admin_page')
    return 'Login failed or not an admin.'

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)