from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# HTML templates as strings for simplicity
login_form = """
<!doctype html>
<title>Login</title>
<h2>Login Form</h2>
<form action="/do_login" method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

admin_page = """
<!doctype html>
<title>Admin Page</title>
<h2>Welcome, Admin!</h2>
<p>You have successfully logged in as an admin.</p>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    # For demonstration, let's assume the admin credentials are:
    if username == 'admin' and password == 'secret':
        return redirect(url_for('admin_page'))
    
    return "Invalid username or password."

@app.route('/admin')
def admin():
    return render_template_string(admin_page)

if __name__ == '__main__':
    app.run(debug=True)