from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def home():
    return "<h1>Welcome to My Simple Web Application</h1>"

if __name__ == '__main__':
    app.run(debug=True)


To run this code, you need to have Flask installed. You can install it using pip:


pip install flask


After installing Flask, save the Python code in a file (e.g., `app.py`) and run it using:


python app.py


This will start a local web server, and you can access your simple web application by navigating to `http://127.0.0.1:5000/` in your web browser.