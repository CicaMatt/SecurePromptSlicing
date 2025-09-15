from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory "database"
users_db = {
    'admin': 'password123'
}

# HTML templates as strings for simplicity
login_page_html = '''
<!doctype html>
<title>Login Page</title>
<h1>Enter your credentials</h1>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

dashboard_html = '''
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard!</h1>
<a href="{{ url_for('login') }}">Logout</a>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Check credentials
        if users_db.get(username) == password:
            return redirect(url_for('dashboard'))
        
        # If incorrect, show login page again
        return render_template_string(login_page_html)
    
    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_html)

if __name__ == '__main__':
    app.run(debug=True)


