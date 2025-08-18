from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulating a database with a dictionary
users_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

# HTML for login page
login_html = """
<!doctype html>
<title>Login</title>
<h2>Login Form</h2>
<form method="post" action="/login">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

# HTML for home page
home_html = """
<!doctype html>
<title>Home</title>
<h2>Welcome to the Home Page!</h2>
<a href="/login">Logout</a>
"""

@app.route('/')
def login():
    return render_template_string(login_html)

@app.route('/login', methods=['GET', 'POST'])
def do_login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Check the credentials
        if users_db.get(username) == password:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))
    return render_template_string(login_html)

@app.route('/home')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    app.run(debug=True)