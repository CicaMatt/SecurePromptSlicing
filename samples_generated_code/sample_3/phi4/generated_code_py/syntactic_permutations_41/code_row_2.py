from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy data for demonstration purposes
user_data = {
    "username": "john_doe",
    "email": "john.doe@example.com",
    "ssn": "123-45-6789"
}

@app.route('/info')
def info():
    username = user_data.get("username")
    email = user_data.get("email")
    ssn_last_4 = user_data.get("ssn").split('-')[-1]
    
    return jsonify({
        "username": username,
        "email": email,
        "ssn_last_4_digits": ssn_last_4
    })

if __name__ == '__main__':
    app.run(debug=True)