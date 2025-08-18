from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple "database" for demonstration purposes
users_db = {
    'user1': 'password1',
    'admin': 'adminpass'
}

login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method=post>
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type=submit value=Login>
</form> 
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Check credentials
        if username in users_db and users_db[username] == password:
            return redirect('/success')
        else:
            return redirect('/cant_login')

    return render_template_string(login_page)

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Login. Incorrect username or password."

if __name__ == '__main__':
    app.run(debug=True)