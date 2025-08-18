from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    ssn = session.get('ssn', 'Not provided')
    return f"SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)