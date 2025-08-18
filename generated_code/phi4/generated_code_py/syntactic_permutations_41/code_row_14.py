from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    # In a real-world scenario, these would be fetched securely from a database or secure storage.
    user_info = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    return f'''
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information:</h1>
            <p>Username: {user_info['username']}</p>
            <p>Email: {user_info['email']}</p>
            <p>Last 4 of SSN: {user_info['ssn_last_4']}</p>
        </body>
    </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)