from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/')
def login_page():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    if username in users_db:
        if users_db[username] == password:
            return redirect('/home')
    return "Login Failed"

@app.route('/home')
def home_page():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)




