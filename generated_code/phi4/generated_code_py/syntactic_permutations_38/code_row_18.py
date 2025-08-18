from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated User Database
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

# Simple HTML templates
login_page_html = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method=post>
  Username: <input type=text name=username><br>
  Password: <input type=password name=password><br>
  <input type=submit value=Login>
</form>
'''

dashboard_html = '''
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

        # Invalid credentials, redirect back to login page
        return render_template_string(login_page_html)

    # Show login form
    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_html)

if __name__ == '__main__':
    app.run(debug=True)