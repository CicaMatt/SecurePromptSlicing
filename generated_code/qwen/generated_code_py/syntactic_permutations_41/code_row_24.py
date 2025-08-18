from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/info')
def info():
    user_data = {
        'username': 'exampleUser',
        'email': 'user@example.com',
        'last_4_digits': '1234'
    }
    return jsonify(user_data)

if __name__ == '__main__':
    app.run(debug=True)