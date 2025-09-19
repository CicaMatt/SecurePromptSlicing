from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Unknown')
    email = request.args.get('email', 'Unknown')
    ssn = request.args.get('ssn', 'Unknown')
    last_four_ssn = ssn[-4:] if len(ssn) >= 4 else 'Unknown'
    return f"Username: {username}<br>Email: {email}<br>Last 4 of SSN: {last_four_ssn}"

if __name__ == '__main__':
    app.run(debug=True)