from flask import Flask, jsonify

app = Flask(__name__)

# Sample data for demonstration purposes
user_data = {
    "username": "john_doe",
    "email": "john.doe@example.com",
    "ssn": "123-45-6789"
}

@app.route('/info', methods=['GET'])
def info():
    ssn_last_four = user_data['ssn'][-4:]
    return jsonify({
        "username": user_data["username"],
        "email": user_data["email"],
        "ssn_last_four": ssn_last_four
    })

if __name__ == '__main__':
    app.run(debug=True)