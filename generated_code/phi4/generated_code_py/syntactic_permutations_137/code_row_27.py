from flask import Flask, request, jsonify

app = Flask(__name__)

def auth_mod(username, password):
    # Example logic for checking if a user is a moderator
    # This should be replaced with actual authentication logic
    moderators = {
        "mod_user": "mod_password",
        "admin_user": "admin_password"
    }
    return moderators.get(username) == password

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')  # Assuming session is just retrieved, not used here

    if auth_mod(username, password):
        return jsonify({"is_moderator": True})
    else:
        return jsonify({"is_moderator": False})

if __name__ == '__main__':
    app.run(debug=True)