from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = "johndoe"
    email = "john.doe@example.com"
    ssn_last_4 = "5678"
    return jsonify({
        "username": username,
        "email": email,
        "ssn_last_4": ssn_last_4
    })

if __name__ == '__main__':
    app.run(debug=True)