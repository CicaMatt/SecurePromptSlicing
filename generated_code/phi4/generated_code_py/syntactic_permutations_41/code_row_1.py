from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulated data retrieval - in a real app, this would come from a database or other secure source.
    user_data = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    response_content = f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {user_data['username']}</p>
            <p>Email: {user_data['email']}</p>
            <p>Last 4 digits of SSN: ****{user_data['ssn_last_4']}</p>
        </body>
    </html>
    """
    
    return response_content

if __name__ == '__main__':
    app.run(debug=True)