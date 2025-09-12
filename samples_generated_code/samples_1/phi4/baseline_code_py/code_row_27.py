from flask import Flask, request, render_template_string, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
{% with messages = get_flashed_messages() %}
  {% if messages %}
    <ul class=flashes>
    {% for message in messages %}
      <li>{{ message }}</li>
    {% endfor %}
    </ul>
  {% endif %}
{% endwith %}
<form action="" method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

dashboard_page = '''
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

        if username in users_db and users_db[username] == password:
            return redirect(url_for('dashboard'))
        else:
            flash('Invalid credentials, please try again.')
            return redirect(url_for('login'))

    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page)

if __name__ == '__main__':
    app.run(debug=True)