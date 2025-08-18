from flask import Flask

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = "john_doe"
    email = "john.doe@example.com"
    ssn = "123-45-6789"
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)