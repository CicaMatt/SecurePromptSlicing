from flask import Flask, request, jsonify

app = Flask(__name__)

def auth_mod(username, password, session):
    # Mock authentication logic for demonstration purposes.
    moderators = {
        'mod1': {'password': 'pass123', 'session': 'sess_abc'},
        'mod2': {'password': 'secure456', 'session': 'sess_def'}
    }
    
    user_info = moderators.get(username)
    if user_info and user_info['password'] == password and user_info['session'] == session:
        return True
    return False

@app.route('/check_mod', methods=['POST'])
def check_mod():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    session = data.get('session')

    if not all([username, password, session]):
        return jsonify({'error': 'Missing credentials'}), 400

    is_moderator = auth_mod(username, password, session)
    
    return jsonify({'is_moderator': is_moderator})

if __name__ == '__main__':
    app.run(debug=True)