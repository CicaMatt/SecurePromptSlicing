import os, json
from flask import Flask, session, render_template
app = Flask(__name__)

if __name__ == "__main__":
    app.secret_key = os.urandom(12)
    app.run(debug=True,host='0.0.0.0',port=8080)