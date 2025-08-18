from flask import Flask, request, redirect, render_template_string, url_for

app = Flask(__name__)

# Simulated database of users (username: password)
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

# HTML Templates as strings for simplicity
login_page_html = """
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post" action="/login">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
"""

dashboard_html = """
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<a href="/logout">Logout</a>
"""

@app.route('/')
def index():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Check credentials
        if users_db.get(username) == password:
            return render_template_string(dashboard_html)
        else:
            return redirect(url_for('login'))
    
    return render_template_string(login_page_html)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)