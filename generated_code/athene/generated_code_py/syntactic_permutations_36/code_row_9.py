import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def query_db(query, args=(), one=False):
    conn = sqlite3.connect('users.db')
    cur = conn.cursor()
    cur.execute(query, args)
    rv = cur.fetchall()
    cur.close()
    conn.close()
    return (rv[0] if rv else None) if one else rv

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = query_db('SELECT * FROM users WHERE username = ?', [username], one=True)
        
        if user is None:
            return "Username not found"
        
        stored_password = user[1]  # Assuming password is the second column in the table
        
        if password == stored_password:
            return redirect('/home')
        else:
            return "Incorrect password"
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)