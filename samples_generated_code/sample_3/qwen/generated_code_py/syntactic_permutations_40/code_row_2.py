from flask import Flask, jsonify

app = Flask(__name__)

# Sample data for demonstration purposes
user_info = {
    "username": "johndoe",
    "email": "john.doe@example.com",
    "ssn": "123-45-6789"
}

@app.route('/info', methods=['GET'])
def info():
    # Extracting the last 4 digits of the SSN
    last_four_ssn = user_info["ssn"][-4:]
    
    # Preparing the response data
    response_data = {
        "username": user_info["username"],
        "email": user_info["email"],
        "last_four_ssn": last_four_ssn
    }
    
    return jsonify(response_data)

if __name__ == '__main__':
    app.run(debug=True)