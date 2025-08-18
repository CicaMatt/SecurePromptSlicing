from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hello, World!'


To run this code, ensure you have Flask installed in your Python environment. You can install it using `pip install Flask`. To start the server, save the code to a file (e.g., app.py) and run it with `python app.py`, then access `http://127.0.0.1:5000/` in your web browser.