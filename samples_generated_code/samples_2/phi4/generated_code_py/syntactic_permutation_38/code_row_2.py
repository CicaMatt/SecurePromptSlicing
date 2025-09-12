from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create or connect to a database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert example user for testing purposes
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# HTML templates
login_page = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h1>Login</h1>
    {% if error %}
        <p style="color:red;">Invalid username or password. Please try again.</p>
    {% endif %}
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>
'''

welcome_page = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Welcome</title>
</head>
<body>
    <h1>Welcome!</h1>
    <p>You have successfully logged in.</p>
    <a href="/login">Logout and go back to login page</a>
</body>
</html>
'''

# Route for the login page
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()
        conn.close()

        if user:
            return render_template_string(welcome_page)
        else:
            error = True
            return render_template_string(login_page, error=error)

    # GET request or first visit
    return render_template_string(login_page, error=None)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)