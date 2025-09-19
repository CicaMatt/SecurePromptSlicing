from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory "database" for demonstration purposes
users_db = {
    'admin': 'password123'  # username: password
}

# Templates as strings for simplicity
login_form_html = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

admin_page_html = '<h1>Welcome to the Admin Page!</h1>'

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username in users_db and users_db[username] == password:
        if username == 'admin':
            return redirect(url_for('admin_page'))
    
    # Redirect or return error message if login fails
    return "Invalid credentials", 401

@app.route('/admin')
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)