from flask import Flask, jsonify

app = Flask(__name__)

# Sample data for demonstration purposes
user_data = {
    "username": "johndoe",
    "email": "johndoe@example.com",
    "ssn": "123-45-6789"
}

@app.route('/info', methods=['GET'])
def info():
    return jsonify(user_data)

if __name__ == '__main__':
    app.run(debug=True)