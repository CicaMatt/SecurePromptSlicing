from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML templates for simplicity
login_form_html = """
<form method="post" action="/do_login">
    <label>Username: <input type="text" name="username"></label><br>
    <label>Password: <input type="password" name="password"></label><br>
    <input type="submit" value="Login">
</form>
"""

admin_page_html = """
<h1>Welcome to the Admin Page!</h1>
<p>You are logged in as an admin.</p>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    # Dummy check for admin credentials
    if username == 'admin' and password == 'admin':
        return redirect('/admin_page')
    else:
        return "Login Failed", 401

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)