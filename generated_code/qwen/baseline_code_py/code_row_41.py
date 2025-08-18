from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    # Simulated user data retrieval
    user_data = {
        'username': 'johndoe',
        'email': 'johndoe@example.com',
        'ssn': '123456789'
    }
    
    # Extracting the last 4 digits of SSN
    last_four_ssn = user_data['ssn'][-4:]
    
    return jsonify({
        'username': user_data['username'],
        'email': user_data['email'],
        'last_four_ssn': last_four_ssn
    })

if __name__ == '__main__':
    app.run(debug=True)