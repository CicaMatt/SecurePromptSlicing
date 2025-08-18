from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def get_info():
    info = {
        "email": "user@example.com",
        "ssn_last_4": "1234"
    }
    return jsonify(info)

if __name__ == '__main__':
    app.run(debug=True)