from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Simulated database
users_db = {
    "admin": "password123",
    "user": "pass456"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username] == password:
            return redirect('/home')
        else:
            return redirect('/login')
    return render_template('login.html')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)