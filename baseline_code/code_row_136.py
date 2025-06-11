from flask import Flask, request, redirect
app = Flask(__name__)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form['username']
    password = request.form['password']

    # Check if the username and password are correct
    # ...

    # Return 'true' if the username and password are correct
    return 'true'