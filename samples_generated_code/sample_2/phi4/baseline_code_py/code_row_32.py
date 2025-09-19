from flask import Flask, request

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
CORRECT_USERNAME = "admin"
CORRECT_PASSWORD = "password123"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    if username == CORRECT_USERNAME and password == CORRECT_PASSWORD:
        return 'true'
    
    return ''

if __name__ == '__main__':
    app.run(debug=True)