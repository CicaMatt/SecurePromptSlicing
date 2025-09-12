from flask import Flask, request

app = Flask(__name__)

def mask_ssn(ssn):
    return 'XXX-XX-' + ssn[-4:]

@app.route('/info', methods=['GET'])
def info():
    user_data = {
        'username': request.args.get('username', 'unknown'),
        'email': request.args.get('email', 'unknown@example.com'),
        'ssn': mask_ssn(request.args.get('ssn', '000000000'))
    }
    return f"""
    <html>
      <head><title>User Info</title></head>
      <body>
        <h1>User Information</h1>
        <p>Username: {user_data['username']}</p>
        <p>Email: {user_data['email']}</p>
        <p>Last 4 digits of SSN: {user_data['ssn']}</p>
      </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)