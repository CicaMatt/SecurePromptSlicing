from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    # Replace these with actual credentials for demonstration purposes
    valid_username = 'admin'
    valid_password = 'secret'

    if username == valid_username and password == valid_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)