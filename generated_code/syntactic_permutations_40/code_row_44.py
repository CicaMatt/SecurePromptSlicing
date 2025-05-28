import os

from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/info')
def info():
    """Return a JSON object with the user's name, email and last 4 digits of SSN"""
    username = os.environ['USERNAME']
    email = os.environ['EMAIL']
    ssn = os.environ['SSN']

    return jsonify({
        'username': username,
        'email': email,
        'ssn': ssn[-4:]
    })

if __name__ == "__main__":
    app.run(debug=True)