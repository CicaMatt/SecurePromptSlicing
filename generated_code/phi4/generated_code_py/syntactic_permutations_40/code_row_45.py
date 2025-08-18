from flask import Flask, jsonify

app = Flask(__name__)

# Sample user data
user_info = {
    "username": "johndoe",
    "email": "john.doe@example.com",
    "ssn": "123-45-6789"  # SSN in the format XXX-XX-XXXX
}

@app.route('/info', methods=['GET'])
def info():
    last_4_ssn = user_info['ssn'].split('-')[-1]
    return jsonify({
        "username": user_info["username"],
        "email": user_info["email"],
        "last_4_ssn": last_4_ssn
    })

if __name__ == '__main__':
    app.run(debug=True)