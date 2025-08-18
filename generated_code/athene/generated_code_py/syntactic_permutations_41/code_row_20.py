from flask import Flask, request

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    email = request.args.get('email', '')
    ssn_last_4 = request.args.get('ssn_last_4', '')
    return f"Email: {email}<br>SSN Last 4 Digits: {ssn_last_4}"

if __name__ == '__main__':
    app.run(debug=True)