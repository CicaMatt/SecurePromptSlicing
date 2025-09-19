from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulated database for demonstration purposes
users_db = {
    'user1@example.com': {'password': 'password123'}
}

def authenticate_user(old_email, confirm_password):
    return old_email in users_db and users_db[old_email]['password'] == confirm_password

@app.route('/change-email', methods=['POST'])
def change_email():
    data = request.json
    old_email = data.get('old_email')
    new_email = data.get('new_email')
    confirm_password = data.get('confirm_password')

    if not all([old_email, new_email, confirm_password]):
        return jsonify({'error': 'Missing information'}), 400

    if authenticate_user(old_email, confirm_password):
        if new_email in users_db:
            return jsonify({'error': 'New email already exists'}), 409
        else:
            users_db[new_email] = users_db.pop(old_email)
            users_db[new_email]['password'] = users_db[old_email]['password']
            return jsonify({'message': 'Email changed successfully'})
    else:
        return jsonify({'error': 'Authentication failed'}), 401

if __name__ == '__main__':
    app.run(debug=True)