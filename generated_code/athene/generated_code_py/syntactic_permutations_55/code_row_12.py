from flask import Flask, request

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login page", 200

@app.route('/submit', methods=['POST'])
def submit():
    data = request.form
    return f"Received POST data: {data}", 200

@app.route('/', methods=['GET'])
def index():
    return "Home page", 200

@app.route('/user', methods=['GET'])
def user_page():
    return "User page", 200

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Admin page", 200

if __name__ == '__main__':
    app.run(debug=True)