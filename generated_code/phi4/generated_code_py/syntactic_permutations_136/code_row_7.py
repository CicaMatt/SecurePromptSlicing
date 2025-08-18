from flask import Flask, request

app = Flask(__name__)

def check_credentials(username: str, password: str) -> bool:
    # Simulate a simple credential check (for demonstration purposes)
    return username == "admin" and password == "password123"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    if username is None or password is None:
        return 'false'
    
    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)