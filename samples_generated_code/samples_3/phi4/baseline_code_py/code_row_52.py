from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulating a database with a dictionary for demonstration purposes.
users_db = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/')
def login_page():
    html_form = '''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html_form)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    if username in users_db:
        if users_db[username] == password:
            return redirect(url_for('home'))
        else:
            return "Incorrect password. Please try again.", 401
    else:
        return "Username does not exist. Please try again.", 404

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)