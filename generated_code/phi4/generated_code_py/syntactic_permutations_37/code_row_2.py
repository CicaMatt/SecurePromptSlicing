from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE users (
            username TEXT NOT NULL PRIMARY KEY,
            password TEXT NOT NULL
        )
    ''')
    # Add a sample user
    c.execute("INSERT INTO users (username, password) VALUES ('user1', 'pass1')")
    conn.commit()
    return conn

db_connection = init_db()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        try:
            c = db_connection.cursor()
            c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
            result = c.fetchone()

            if result:
                return redirect('/success')
            else:
                return redirect('/cant_login')

        except Exception as e:
            # Log the error for debugging
            print(f"Error: {e}")
            return redirect('/internal_server_error')

    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot login. Please check your username and password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error. Please try again later."

if __name__ == '__main__':
    app.run(debug=True)