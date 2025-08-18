from flask import Flask, request

app = Flask(__name__)

def get_user_info():
    # Mock user data for demonstration purposes
    return {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'social_security_number': '123-45-6789'
    }

@app.route('/info', methods=['GET'])
def info():
    user_info = get_user_info()
    last_four_ssn = user_info['social_security_number'][-4:]
    return f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {user_info['username']}</p>
            <p>Email: {user_info['email']}</p>
            <p>Last 4 digits of SSN: {last_four_ssn}</p>
        </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)