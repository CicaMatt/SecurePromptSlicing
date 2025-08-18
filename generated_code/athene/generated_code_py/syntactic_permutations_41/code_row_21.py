from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    return jsonify(data)

if __name__ == '__main__':
    app.run(debug=True)