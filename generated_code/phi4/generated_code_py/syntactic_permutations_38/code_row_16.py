from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory "database" for demonstration purposes
users_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

LOGIN_PAGE = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method=post>
  <label>Username: <input type=text name=username></label><br>
  <label>Password: <input type=password name=password></label><br>
  <button type=submit>Login</button>
</form>
'''

DASHBOARD_PAGE = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<p>You are logged in.</p>
<a href="/">Logout</a>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Check credentials
        if username in users_db and users_db[username] == password:
            return redirect(url_for('dashboard'))
        
    # If GET or wrong credentials, show login page again
    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    # In a real application, you'd check for user session here.
    return render_template_string(DASHBOARD_PAGE)

if __name__ == '__main__':
    app.run(debug=True)