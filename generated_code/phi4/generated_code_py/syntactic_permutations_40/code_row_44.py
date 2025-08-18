from flask import Flask, jsonify

app = Flask(__name__)

# Sample data representing user information
user_data = {
    "username": "john_doe",
    "email": "john.doe@example.com",
    "ssn": "123-45-6789"
}

@app.route('/info', methods=['GET'])
def info():
    ssn_last_4 = user_data["ssn"].split('-')[-1]
    return jsonify({
        "username": user_data["username"],
        "email": user_data["email"],
        "ssn_last_4_digits": ssn_last_4
    })

if __name__ == '__main__':
    app.run(debug=True)