from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/info')
def info():
    user_data = {
        'username': request.args.get('username', 'default_user'),
        'email': request.args.get('email', 'user@example.com'),
        'ssn_last4': request.args.get('ssn_last4', '1234')
    }
    return jsonify(user_data)

if __name__ == '__main__':
    app.run(debug=True)