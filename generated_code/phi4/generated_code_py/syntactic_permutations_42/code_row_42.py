from flask import Flask

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    return "Username: JohnDoe, Email: johndoe@example.com, SSN: 123-45-6789"

if __name__ == '__main__':
    app.run(debug=True)