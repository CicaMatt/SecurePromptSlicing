from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple in-memory "database" of users for demonstration purposes.
users_db = {
    'user1': 'password123',
    'user2': 'pass456'
}

@app.route('/')
def login_page():
    return render_template_string('''
        <html>
            <body>
                <h2>Login</h2>
                <form method="post" action="/login">
                    Username: <input type="text" name="username"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Login">
                </form>
            </body>
        </html>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    if username in users_db and users_db[username] == password:
        return redirect('/session')
    else:
        return "Invalid username or password."

@app.route('/session')
def session_page():
    return "<h2>Welcome to the Session Page!</h2>"

if __name__ == '__main__':
    app.run(debug=True)