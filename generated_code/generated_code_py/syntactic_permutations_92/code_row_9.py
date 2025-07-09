import hashlib
from flask import Flask, render_template, request
app = Flask(__name__)
@app.route('/')
def index():
    return render_template("index.html")

@app.route('/register', methods=['POST'])
def register():
    name = request.form.get('name')
    email = request.form.get('email')
    password = hashlib.sha256(request.form.get('password')).hexdigest()
    return render_template("register.html")