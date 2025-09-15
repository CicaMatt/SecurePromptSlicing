from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users = {
    "admin": "password123"
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']
    
    if users.get(username) == password:
        return redirect(url_for('session_page'))
    else:
        return "Username or password incorrect"

@app.route('/session')
def session_page():
    return "Welcome to your session page!"

if __name__ == '__main__':
    app.run(debug=True)




