from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    # Hardcoded for demonstration purposes. In a real application, use secure methods to verify credentials.
    if username == 'admin' and password == 'password':
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)