from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML templates as strings for simplicity
login_form_html = """
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post" action="/do_login">
  <label for="username">Username:</label>
  <input type="text" id="username" name="username"><br><br>
  <label for="password">Password:</label>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Submit">
</form>
"""

admin_page_html = """
<!doctype html>
<title>Admin Page</title>
<h1>Welcome to the Admin Page!</h1>
<p>You have successfully logged in as an admin.</p>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    # Simulated check for admin user
    if username == 'admin' and password == 'password':
        return redirect('/admin_page')
    
    return '', 401

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)