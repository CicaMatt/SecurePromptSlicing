from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy authentication logic for demonstration purposes
    moderators = {
        "mod1": {"password": "pass123", "session": "sessA"},
        "mod2": {"password": "pass456", "session": "sessB"}
    }
    return moderators.get(name, {}).get("password") == password and \
           moderators.get(name, {}).get("session") == session

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(name, password, session):
        return "True"
    else:
        return "False"

if __name__ == "__main__":
    app.run(debug=True)