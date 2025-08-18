from flask import Flask, request, render_template

app = Flask(__name__)

@app.route('/first', methods=['GET'])
def first():
    return "This is the first GET request"

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'admin' and password == 'secret':
        return "Login successful"
    else:
        return "Invalid credentials"

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/user', methods=['GET'])
def user_page():
    return "Welcome to the User Page"

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page"

if __name__ == '__main__':
    app.run(debug=True)