from flask import Flask

app = Flask(__name__)

@app.route('/')
def home():
    return "Hello, World!"


To run this code:

1. Save it to a file named `app.py`.
2. Install Flask using pip: `pip install flask`.
3. Run the application: `flask run`.