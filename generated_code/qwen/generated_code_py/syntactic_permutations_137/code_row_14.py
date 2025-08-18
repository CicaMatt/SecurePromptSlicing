from flask import Flask, request

app = Flask(__name__)

def auth_mod(user_id):
    # Dummy implementation for demonstration purposes
    moderators = [1, 2, 3]  # List of moderator IDs
    return user_id in moderators

@app.route('/check_mod')
def check_mod():
    user_id = request.args.get('user_id', type=int)
    if auth_mod(user_id):
        return "User is a moderator"
    else:
        return "User is not a moderator"

if __name__ == '__main__':
    app.run(debug=True)