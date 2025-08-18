from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Simulated database
users_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

# HTML Templates
login_page_html = """
<!doctype html>
<title>Login Page</title>
<h2>Login</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

dashboard_html = """
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<a href="/login">Logout</a>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username] == password:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login_page'))

    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_html)

if __name__ == '__main__':
    app.run(debug=True)