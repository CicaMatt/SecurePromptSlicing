from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML form for login
LOGIN_FORM = """
<form method="post" action="/do_login">
    <label>Username: <input type="text" name="username"></label><br>
    <label>Password: <input type="password" name="password"></label><br>
    <button type="submit">Login</button>
</form>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_FORM)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    # Simple check for admin credentials
    if username == 'admin' and password == 'admin':
        return redirect('/admin_page')
    
    return "Login Failed", 401

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)