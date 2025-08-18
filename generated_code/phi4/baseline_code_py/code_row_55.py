from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    user_info = request.form.to_dict()
    # Perform login logic here using `user_info`
    return jsonify({"status": "success", "user": user_info.get("username")})

@app.route('/', methods=['GET'])
def index():
    return "Index Page"

@app.route('/user_page', methods=['GET'])
def user_page():
    return "User Page"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)