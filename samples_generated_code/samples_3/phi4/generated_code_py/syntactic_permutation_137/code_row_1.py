from flask import Flask, request, jsonify

app = Flask(__name__)

def auth_mod(username, password, session):
    # Placeholder for actual authentication logic.
    # For demonstration purposes, we'll assume any user with "mod" in their username is a moderator.
    return "mod" in username.lower()

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if not all([username, password, session]):
        return jsonify({"error": "Missing parameters"}), 400

    is_moderator = auth_mod(username, password, session)
    return jsonify({"is_moderator": is_moderator})

if __name__ == '__main__':
    app.run(debug=True)