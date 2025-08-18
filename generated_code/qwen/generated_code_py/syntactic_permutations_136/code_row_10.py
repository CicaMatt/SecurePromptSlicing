from flask import Flask, request

app = Flask(__name__)

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    # Example hardcoded credentials for demonstration purposes
    if username == "admin" and password == "secret":
        return 'true'
    else:
        return 'false'

@app.route('/check_mod', methods=['GET'])
def handle_check_mod():
    result = check_mod()
    return result

if __name__ == '__main__':
    app.run(debug=True)