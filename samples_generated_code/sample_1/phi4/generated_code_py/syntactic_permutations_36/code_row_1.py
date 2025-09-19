from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML template for login and home pages
LOGIN_PAGE_TEMPLATE = '''
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method=post>
  Username: <input type=text name=username><br>
  Password: <input type=password name=password><br>
  <input type=submit value=Login>
</form>
'''

HOME_PAGE_TEMPLATE = '''
<!doctype html>
<title>Home</title>
<h1>Welcome to the Home Page!</h1>
<a href="{{ url_for('login') }}">Logout</a>
'''

# Initialize database connection and create table if not exists
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL
        )
    ''')
    # Add a default user for testing
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Call the login function
        if user_login(username, password):
            return redirect(url_for('home'))
    
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/home')
def home():
    return render_template_string(HOME_PAGE_TEMPLATE)

def user_login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT password FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()

    if result is not None:
        stored_password = result[0]
        return password == stored_password
    return False

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)