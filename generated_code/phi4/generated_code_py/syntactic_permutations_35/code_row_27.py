from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy data for username and password validation
USERS = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/login', methods=['GET'])
def login_form():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    if username in USERS and USERS[username] == password:
        return redirect(url_for('home'))
    else:
        return redirect(url_for('login_form'))

@app.route('/')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)




