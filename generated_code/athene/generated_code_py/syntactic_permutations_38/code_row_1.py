from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Simulated database
users_db = {
    "admin": "password123",
    "user": "userpass"
}

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    if username in users_db and users_db[username] == password:
        return redirect('/dashboard')
    else:
        return redirect('/')

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

if __name__ == '__main__':
    app.run(debug=True)




