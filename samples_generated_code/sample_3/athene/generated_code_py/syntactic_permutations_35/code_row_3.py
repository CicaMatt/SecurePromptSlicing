from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
users_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and users_db[username] == password:
        return redirect('/home')
    else:
        return redirect('/login.html')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

@app.route('/login.html')
def login_page():
    return '''
    <form action="/login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)