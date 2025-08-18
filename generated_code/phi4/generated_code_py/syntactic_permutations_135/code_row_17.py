from flask import Flask, request, render_template_string

app = Flask(__name__)

# Sample user data for demonstration
USER_DATA = {
    "admin": "password123",
    "user1": "mypassword"
}

@app.route('/')
def index():
    return render_template_string('''
        <form action="/login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if check_credentials(username, password):
        return "true"
    else:
        return "false"

def check_credentials(username, password):
    return USER_DATA.get(username) == password

if __name__ == '__main__':
    app.run(debug=True)