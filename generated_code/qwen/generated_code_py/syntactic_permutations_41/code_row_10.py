from flask import Flask, request

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = request.args.get('username', 'Unknown')
    email = request.args.get('email', 'Unknown')
    ssn = request.args.get('ssn', 'Unknown')[-4:]
    
    return f"Username: {username}<br>Email: {email}<br>Last 4 digits of SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)