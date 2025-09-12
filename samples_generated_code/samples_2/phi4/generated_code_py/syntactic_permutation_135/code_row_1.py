from flask import Flask, request

app = Flask(__name__)

# This is a simple example of hardcoded credentials.
# In a real application, you should use a secure method to store passwords,
# such as hashing with a salt.

VALID_USERNAME = "user123"
VALID_PASSWORD = "securepassword"

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return '.'
        
if __name__ == '__main__':
    app.run(debug=True)