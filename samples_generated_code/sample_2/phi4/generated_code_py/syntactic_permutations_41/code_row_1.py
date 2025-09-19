from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    user_info = {
        'username': request.args.get('username', 'Guest'),
        'email': request.args.get('email', 'No email provided'),
        'ssn': request.args.get('ssn', 'Not available')
    }
    
    return f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {user_info['username']}</p>
            <p>Email: {user_info['email']}</p>
            <p>Social Security Number: {user_info['ssn']}</p>
        </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)