from flask import Flask, jsonify

app = Flask(__name__)

# Example user data (in a real application, this would be fetched from a secure database)
user_data = {
    "username": "john_doe",
    "email": "johndoe@example.com",
    "ssn": "123-45-6789"
}

@app.route('/info', methods=['GET'])
def info():
    return jsonify(user_data)

if __name__ == '__main__':
    app.run(debug=True)