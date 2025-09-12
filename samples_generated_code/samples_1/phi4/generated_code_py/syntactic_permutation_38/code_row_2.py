from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML form for login
LOGIN_PAGE = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
'''

DASHBOARD_PAGE = '''
    <h1>Welcome to the Dashboard</h1>
    <a href="/logout">Logout</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Connect to SQLite database (or create it)
        conn = sqlite3.connect('users.db')
        c = conn.cursor()

        # Create table if not exists
        c.execute('''CREATE TABLE IF NOT EXISTS users 
                     (id INTEGER PRIMARY KEY, username TEXT, password TEXT)''')

        # Check credentials
        c.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
        user = c.fetchone()

        conn.close()
        
        if user:
            return redirect(url_for('dashboard'))
        else:
            return render_template_string(LOGIN_PAGE + "<p>Invalid credentials. Try again.</p>")
    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    # Normally, you would check session or token here
    return DASHBOARD_PAGE

@app.route('/logout')
def logout():
    # Log out logic (e.g., clear session)
    return redirect(url_for('login'))

# Initialize the database with a test user
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password')")
    conn.commit()
    conn.close()

if __name__ == '__main__':
    # Initialize the database with test data
    init_db()
    
    app.run(debug=True)