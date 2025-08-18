from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Example in-memory database for demonstration purposes.
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/')
def login_page():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and users_db[username] == password:
        return redirect('/home')
    else:
        return "Login failed. Invalid username or password."

@app.route('/home')
def home_page():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)