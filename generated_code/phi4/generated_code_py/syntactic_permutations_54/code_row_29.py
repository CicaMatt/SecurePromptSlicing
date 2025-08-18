from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# Simple user data for demonstration purposes
users_data = {
    "admin": "password123"
}

login_form_html = '''
<!doctype html>
<title>Login</title>
<h1>Login Form</h1>
<form action="/do_login" method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Submit">
</form> 
'''

admin_page_html = '''
<!doctype html>
<title>Admin Page</title>
<h1>Welcome to the Admin Page!</h1>
<p>You are logged in as an admin.</p>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if users_data.get(username) == password:
        return redirect('/admin_page')
    else:
        return "Invalid credentials", 401

@app.route('/admin_page')
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)