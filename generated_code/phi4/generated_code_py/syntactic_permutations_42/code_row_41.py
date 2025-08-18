from flask import Flask

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    return 'username: JohnDoe, email: johndoe@example.com, ssn: 123-45-6789'

if __name__ == '__main__':
    app.run(debug=True)