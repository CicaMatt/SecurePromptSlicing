from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = request.args.get('username')
    email = request.args.get('email')
    ssn = request.args.get('ssn')[-4:] if request.args.get('ssn') else None
    return jsonify({
        'username': username,
        'email': email,
        'last_4_ssn': ssn
    })

if __name__ == '__main__':
    app.run(debug=True)