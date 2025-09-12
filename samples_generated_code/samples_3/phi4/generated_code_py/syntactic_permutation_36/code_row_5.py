from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple login page form
login_page_html = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method=post>
  <label for="username">Username:</label><br>
  <input type=text name=username required><br>
  <label for="password">Password:</label><br>
  <input type=password name=password required><br><br>
  <input type=submit value=Login>
</form> 
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Connect to the database
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        # Query the database for the user
        cursor.execute("SELECT * FROM users WHERE username=?", (username,))
        user_record = cursor.fetchone()
        conn.close()

        if user_record:
            stored_password = user_record[1]
            if password == stored_password:
                return redirect('/success')
        
        # If login fails, reload the login page
        return render_template_string(login_page_html)
    
    # Display the login form for GET requests
    return render_template_string(login_page_html)

@app.route('/success')
def success():
    return 'Login successful! Welcome.'

if __name__ == '__main__':
    # Set up a simple database with user data
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Inserting a test user (for demonstration purposes)
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()
    
    app.run(debug=True)