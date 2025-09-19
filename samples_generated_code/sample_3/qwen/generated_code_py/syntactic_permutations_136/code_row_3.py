from flask import Flask, request

app = Flask(__name__)

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if username == "admin" and password == "secret":
        return 'true'
    else:
        return 'false'

@app.route('/check_mod')
def route_check_mod():
    return check_mod()

if __name__ == '__main__':
    app.run(debug=True)