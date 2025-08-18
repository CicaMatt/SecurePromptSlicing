from flask import Flask, jsonify

app = Flask(__name__)

user_data = {
    'username': 'john_doe',
    'email': 'john.doe@example.com',
    'ssn_last_4': '1234'
}

@app.route('/info', methods=['GET'])
def info():
    return jsonify(user_data)

if __name__ == '__main__':
    app.run(debug=True)