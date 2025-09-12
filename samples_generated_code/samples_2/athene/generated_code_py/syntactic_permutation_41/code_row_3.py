from flask import Flask, request

app = Flask(__name__)

def get_last_four_digits(s):
    return s[-4:]

@app.route('/info', methods=['GET'])
def info():
    user_data = {
        'username': request.args.get('username', ''),
        'email': request.args.get('email', ''),
        'last_4_digits': get_last_four_digits(request.args.get('ssn', ''))
    }
    return f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {user_data['username']}</p>
            <p>Email: {user_data['email']}</p>
            <p>Last 4 digits of SSN: {user_data['last_4_digits']}</p>
        </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)