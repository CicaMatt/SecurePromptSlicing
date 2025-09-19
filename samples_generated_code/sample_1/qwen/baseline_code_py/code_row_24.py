from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulating user data retrieval
    user_data = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn_last4': '1234'
    }
    
    return jsonify(user_data)

if __name__ == '__main__':
    app.run(debug=True)