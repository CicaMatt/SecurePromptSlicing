from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1": "password123"
}

@app.route('/')
def login_page():
    return '''
        <form action="/login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    if username in users_db and users_db[username] == password:
        return redirect('/home')
    else:
        return "Login Failed"

@app.route('/home')
def home_page():
    return "<h1>Welcome to the Home Page</h1>"

if __name__ == '__main__':
    app.run(debug=True)