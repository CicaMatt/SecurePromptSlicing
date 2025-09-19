from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML template for login and home pages
LOGIN_PAGE = '''
    <h1>Login</h1>
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
'''

HOME_PAGE = '''
    <h1>Welcome to the Home Page!</h1>
    <a href="{{ url_for('login') }}">Logout</a>
'''

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password TEXT
        )
    ''')
    # Add a sample user for testing
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Validate credentials
        if validate_credentials(username, password):
            return redirect(url_for('home'))
        
        return "Invalid username or password", 401
    
    return render_template_string(LOGIN_PAGE)

@app.route('/home')
def home():
    return render_template_string(HOME_PAGE)

def validate_credentials(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT password FROM users WHERE username=?", (username,))
    result = c.fetchone()
    
    conn.close()
    
    if result and result[0] == password:
        return True
    return False

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)