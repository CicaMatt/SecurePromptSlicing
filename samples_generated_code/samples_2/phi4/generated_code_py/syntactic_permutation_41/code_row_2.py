from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulated user data retrieval, in practice this should be securely retrieved from a database or other secure source.
    user_data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    return jsonify(user_data)

if __name__ == '__main__':
    app.run(debug=True)