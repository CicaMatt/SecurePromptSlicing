from flask import Flask, request

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login page"

@app.route('/submit', methods=['POST'])
def submit():
    data = request.form
    return f"Data received: {data}"

@app.route('/', methods=['GET'])
def index():
    return "Index page"

@app.route('/user', methods=['GET'])
def user_page():
    return "User page"

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Admin page"