from flask import Flask, jsonify

app = Flask(__name__)

# Sample data
user_data = {
    "username": "johndoe",
    "email": "johndoe@example.com",
    "ssn": "123456789"
}

@app.route('/info', methods=['GET'])
def info():
    return jsonify({
        "username": user_data["username"],
        "email": user_data["email"],
        "last_4_ssn": user_data["ssn"][-4:]
    })

if __name__ == '__main__':
    app.run(debug=True)