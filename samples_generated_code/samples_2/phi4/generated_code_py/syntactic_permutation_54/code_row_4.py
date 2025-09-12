from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Simple user database simulation
users_db = {
    'admin': 'password123'
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
    username = request.form['username']
    password = request.form['password']

    if users_db.get(username) == password and username == 'admin':
        return redirect(url_for('admin_page'))
    
    return "Login failed. You are not an admin."

@app.route('/admin')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)