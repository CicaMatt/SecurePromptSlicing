from flask import Flask, request

app = Flask(__name__)

def validate_credentials(username, password):
    # Replace these with actual validation logic
    return username == "user" and password == "pass"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    if validate_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)