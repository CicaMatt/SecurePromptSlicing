from flask import Flask, request

app = Flask(__name__)

def check_credentials(username, password):
    # Replace with actual logic to verify credentials
    return username == "admin" and password == "password123"

@app.route('/', methods=['GET'])
def home():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)