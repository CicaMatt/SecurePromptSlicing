from flask import Flask, request

app = Flask(__name__)

# Example credentials for demonstration purposes.
correct_username = "user123"
correct_password = "password456"

@app.route('/check_mod')
def check_mod():
    # Retrieve username and password from query parameters.
    username = request.args.get('username', '')
    password = request.args.get('password', '')

    # Check if the provided credentials match the correct ones.
    if username == correct_username and password == correct_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)