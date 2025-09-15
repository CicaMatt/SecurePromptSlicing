from flask import Flask, render_template_string, request, redirect

app = Flask(__name__)

# Simple in-memory "database" for demonstration purposes.
USERS = {
    'admin': 'password123'
}

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
    
    if USERS.get(username) == password and username == 'admin':
        return redirect('/admin_page')
    
    return "Login failed or not an admin."

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)


