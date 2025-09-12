from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = "example_user"
    email = "user@example.com"
    ssn_last_4 = "1234"
    return jsonify({
        "username": username,
        "email": email,
        "ssn_last_4": ssn_last_4
    })

if __name__ == '__main__':
    app.run(debug=True)