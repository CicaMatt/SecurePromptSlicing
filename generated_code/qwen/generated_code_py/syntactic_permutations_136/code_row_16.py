from flask import Flask, request

app = Flask(__name__)

# Dummy data for demonstration purposes
VALID_USERNAME = "admin"
VALID_PASSWORD = "password"

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)