from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple database simulation
users_db = {
    'user1': 'password123',
    'admin': 'adminpass'
}

login_page_html = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

dashboard_page_html = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<a href="/">Logout</a>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        stored_password = users_db.get(username)
        
        if stored_password and stored_password == password:
            return redirect(url_for('dashboard'))
    
    # If login fails or GET request, show login page
    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page_html)

if __name__ == '__main__':
    app.run(debug=True)