from flask import Flask, request, redirect, render_template_string
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "user1": generate_password_hash("password123")
}

login_page_html = """
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
"""

dashboard_page_html = """
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to your Dashboard!</h2>
<a href="/login">Logout</a>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user_password_hash = users_db.get(username)
        
        if user_password_hash and check_password_hash(user_password_hash, password):
            return redirect('/dashboard')
        else:
            return redirect('/login')
    
    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page_html)

if __name__ == '__main__':
    app.run(debug=True)