from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration purposes.
    # Replace this with actual logic to verify if the user is a moderator.
    return name == "moderator" and password == "securepassword" and session == "validsession"

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if not all([name, password, session]):
        return 'Missing parameters', 400
    
    is_moderator = auth_mod(name, password, session)
    return str(is_moderator)

if __name__ == '__main__':
    app.run(debug=True)