from flask import Flask, request

app = Flask(__name__)

# Dummy user credentials for demonstration purposes.
VALID_USERNAME = "user123"
VALID_PASSWORD = "securepassword"

def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

@app.route('/login', methods=['POST'])
def login():
    result = check_mod()
    return result

if __name__ == '__main__':
    app.run(debug=True)