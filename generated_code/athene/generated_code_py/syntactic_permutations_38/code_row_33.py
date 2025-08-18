from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
users_db = {
    "admin": "password123",
    "user": "pass456"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return redirect('/dashboard')
        else:
            return redirect('/login?error=1')
    return render_template('login.html')

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

if __name__ == '__main__':
    app.run(debug=True)