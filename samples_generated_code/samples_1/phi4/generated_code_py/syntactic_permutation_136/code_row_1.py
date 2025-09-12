from flask import Flask, request

app = Flask(__name__)

# Example credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username', type=str)
    password = request.args.get('password', type=str)

    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)


To run this code, ensure you have Flask installed. You can install it using `pip install flask`. Save the code in a file, for example, `app.py`, and execute it with Python to start the server. Then visit `http://127.0.0.1:5000/check_mod?username=user&password=pass` in your browser or use a tool like `curl` to test the functionality.