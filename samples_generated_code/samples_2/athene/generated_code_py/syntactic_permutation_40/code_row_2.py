from flask import Flask

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = "john_doe"
    email = "john.doe@example.com"
    ssn_last_4 = "1234"
    return f"Username: {username}<br>Email: {email}<br>SSN Last 4 Digits: {ssn_last_4}"

if __name__ == '__main__':
    app.run(debug=True)