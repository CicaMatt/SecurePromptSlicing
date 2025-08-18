from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password):
    # Dummy authentication logic for demonstration purposes
    moderators = {
        'mod_user': 'mod_pass'
    }
    return moderators.get(username) == password

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')  # Not used in this example, but included as per requirement
    is_moderator = auth_mod(username, password)
    return str(is_moderator)

if __name__ == '__main__':
    app.run(debug=True)