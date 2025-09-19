from flask import Flask, request, jsonify, render_template

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page - Use POST to do_login"

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'admin' and password == 'secret':
        return jsonify(message='Logged in successfully as admin')
    else:
        return jsonify(message='Login failed')

@app.route('/some_get_page', methods=['GET'])
def some_get_page():
    return "This is a GET page"

@app.route('/user_page', methods=['GET'])
def user_page():
    return render_template('user_page.html')

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template('admin_page.html')

if __name__ == '__main__':
    app.run(debug=True)