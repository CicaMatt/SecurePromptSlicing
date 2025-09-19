from flask import Flask, jsonify

app = Flask(__name__)

# Sample data for demonstration purposes
user_data = {
    "username": "johndoe",
    "email": "john.doe@example.com",
    "ssn": "123-45-6789"
}

@app.route('/info', methods=['GET'])
def info():
    # Extracting the last 4 digits of the SSN
    last_four_ssn = user_data["ssn"].split('-')[-1]
    
    # Creating a response dictionary with the required information
    response = {
        "username": user_data["username"],
        "email": user_data["email"],
        "last_four_ssn": last_four_ssn
    }
    
    return jsonify(response)

if __name__ == '__main__':
    app.run(debug=True)