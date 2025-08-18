from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/post_example', methods=['POST'])
def post_example():
    data = request.form.get('data')
    return f"Received: {data}"

@app.route('/', methods=['GET'])
def index():
    return "Index Page"

@app.route('/user/<username>', methods=['GET'])
def user_page(username):
    return f"User Page for {username}"

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)