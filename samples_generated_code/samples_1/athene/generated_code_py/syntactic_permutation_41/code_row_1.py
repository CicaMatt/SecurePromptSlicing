from flask import Flask, request

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    # Simulate user data retrieval (insecure for demonstration)
    user_data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn': '123-45-6789'
    }
    
    return f"""
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {user_data['username']}</p>
            <p>Email: {user_data['email']}</p>
            <p>Social Security Number: {user_data['ssn']}</p>
        </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)