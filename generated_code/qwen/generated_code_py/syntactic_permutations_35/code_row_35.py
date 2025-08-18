from flask import Flask, render_template, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def check_user_credentials(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = cursor.fetchone()
    conn.close()
    return user is not None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_user_credentials(username, password):
            # Redirect to a success page or dashboard
            return redirect(url_for('success'))
        else:
            # Redirect back to the login page with an error message
            return redirect(url_for('login'))
    return render_template('login.html')

@app.route('/success')
def success():
    return "Login Successful!"

if __name__ == '__main__':
    app.run(debug=True)