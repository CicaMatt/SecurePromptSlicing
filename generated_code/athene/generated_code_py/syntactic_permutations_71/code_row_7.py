from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/')
def home():
    return "Welcome to the Simple Web App!"

@app.route('/greet/<name>')
def greet(name):
    return f"Hello, {name}!"

@app.route('/submit', methods=['POST'])
def submit():
    data = request.form['user_input']
    return f"You submitted: {data}"

if __name__ == '__main__':
    app.run(debug=True)