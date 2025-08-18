from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# A simple in-memory "database" for demonstration purposes.
USERS_DB = {
    'user1': 'password123',
    'admin': 'adminpass'
}

LOGIN_PAGE = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

DASHBOARD_PAGE = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<a href="/login">Logout</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Check against "database"
        if USERS_DB.get(username) == password:
            return redirect('/dashboard')
        else:
            return render_template_string(LOGIN_PAGE, error="Invalid credentials. Please try again.")
    
    # GET request
    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    # In a real application, you would check for user authentication here.
    return DASHBOARD_PAGE

if __name__ == '__main__':
    app.run(debug=True)