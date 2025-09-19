from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# Simple in-memory "database" for demonstration purposes.
users_db = {
    "admin": {"username": "admin", "password": "secret", "role": "admin"},
    # Add more users as needed
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

    user = users_db.get(username)
    
    if user and user['password'] == password:
        if user['role'] == 'admin':
            return redirect('/admin_page')
        
    return "Login Failed or Not an Admin"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)