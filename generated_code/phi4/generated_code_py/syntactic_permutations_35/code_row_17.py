from flask import Flask, request, redirect, url_for, render_template_string, flash
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# HTML templates
login_html = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
{% with messages = get_flashed_messages() %}
  {% if messages %}
    <ul>
    {% for message in messages %}
      <li>{{ message }}</li>
    {% endfor %}
    </ul>
  {% endif %}
{% endwith %}
'''

home_html = '''
<!doctype html>
<title>Home</title>
<h2>Welcome Home!</h2>
<a href="{{ url_for('login') }}">Logout</a>
'''

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Adding a test user for demonstration purposes
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()

        if user:
            return redirect(url_for('home'))
        else:
            flash('Invalid username or password')
    
    return render_template_string(login_html)

@app.route('/home')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    app.run(debug=True)