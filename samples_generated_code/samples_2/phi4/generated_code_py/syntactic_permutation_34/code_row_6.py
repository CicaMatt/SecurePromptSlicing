from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulating a database with a dictionary for demonstration purposes.
users_db = {
    'admin': 'password123'
}

login_page_html = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
'''

dashboard_page_html = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<a href="{{ url_for('login') }}">Logout</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Check credentials
        if users_db.get(username) == password:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login'))

    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page_html)

if __name__ == '__main__':
    app.run(debug=True)