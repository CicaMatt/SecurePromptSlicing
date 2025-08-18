from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def user_profile():
    # Mocked user data for demonstration purposes
    user_data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    return f"""
    <html>
        <head><title>User Profile</title></head>
        <body>
            <h1>{user_data['username']}</h1>
            <p>Email: {user_data['email']}</p>
            <p>SSN Last 4 Digits: {user_data['ssn_last_4']}</p>
        </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)