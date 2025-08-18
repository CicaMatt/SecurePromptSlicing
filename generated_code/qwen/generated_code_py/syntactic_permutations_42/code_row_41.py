from flask import Flask

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = "example_user"
    email = "user@example.com"
    ssn = "123-45-6789"
    return f"Username: {username}\nEmail: {email}\nSSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)