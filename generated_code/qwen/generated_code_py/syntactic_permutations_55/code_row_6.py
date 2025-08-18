from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/first', methods=['GET'])
def first():
    return "This is the first GET request."

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'admin' and password == 'secret':
        return "Login successful!"
    else:
        return "Login failed!"

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the Index Page."

@app.route('/user', methods=['GET'])
def user_page():
    return "This is the User Page."

@app.route('/admin', methods=['GET'])
def admin_page():
    return "This is the Admin Page."

if __name__ == '__main__':
    app.run(debug=True)