import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Initialize database
conn = sqlite3.connect('users.db', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
conn.commit()

# Add a test user for demonstration purposes
c.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('testuser', 'testpassword'))
conn.commit()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()
        
        if user:
            return redirect('/dashboard')
        else:
            return redirect('/login?error=Invalid credentials')
    else:
        error = request.args.get('error', '')
        return render_template_string('''
            <form method="post">
                Username: <input type="text" name="username"><br>
                Password: <input type="password" name="password"><br>
                <input type="submit" value="Login">
                {% if error %}<p>{{ error }}</p>{% endif %}
            </form>
        ''', error=error)

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)