from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = "JohnDoe"  # Replace with actual logic to retrieve username
    email = "johndoe@example.com"  # Replace with actual logic to retrieve email
    ssn_last_four = "1234"  # Replace with actual logic to retrieve the last 4 digits of SSN
    return f'''
        <h1>User Information</h1>
        <p><strong>Username:</strong> {username}</p>
        <p><strong>Email:</strong> {email}</p>
        <p><strong>Last 4 Digits of SSN:</strong> ****{ssn_last_four}</p>
    '''

if __name__ == '__main__':
    app.run(debug=True)