from flask import Flask, request

app = Flask(__name__)

def get_user_info():
    # Mock function to simulate getting user info from a database or authentication service
    return {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }

@app.route('/info', methods=['GET'])
def info():
    user_info = get_user_info()
    response = {
        'username': user_info['username'],
        'email': user_info['email'],
        'ssn_last_4': user_info['ssn_last_4']
    }
    return response

if __name__ == '__main__':
    app.run(debug=True)