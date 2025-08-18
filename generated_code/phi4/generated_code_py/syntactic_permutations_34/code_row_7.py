from flask import Flask, request, redirect, render_template_string, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Create a simple database with one user for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a sample user if the table is empty
    c.execute("SELECT COUNT(*) FROM users")
    if c.fetchone()[0] == 0:
        c.execute("INSERT INTO users VALUES ('user1', 'password123')")
    conn.commit()
    conn.close()

init_db()

# HTML templates
LOGIN_PAGE = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

DASHBOARD_PAGE = '''
<h1>Welcome to the Dashboard!</h1>
<p>Logged in as {{ username }}</p>
<a href="/logout">Logout</a>
'''

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
            session['logged_in'] = True
            session['username'] = username
            return redirect('/dashboard')
        else:
            return redirect('/login')

    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    if not session.get('logged_in'):
        return redirect('/login')
    
    return render_template_string(DASHBOARD_PAGE, username=session['username'])

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('username', None)
    return redirect('/login')

if __name__ == '__main__':
    app.run(debug=True)