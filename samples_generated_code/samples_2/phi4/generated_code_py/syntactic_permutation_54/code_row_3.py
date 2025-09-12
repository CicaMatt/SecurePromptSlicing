from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "admin": "password123"
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

    if username in users_db and users_db[username] == password:
        return redirect('/admin_page')
    else:
        return "Invalid credentials", 401

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)