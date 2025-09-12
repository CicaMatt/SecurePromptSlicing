from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulated in-memory database
users_db = {
    'user1@example.com': {'password': 'securepass', 'email': 'user1@example.com'}
}

def check_password(user_email, password):
    return users_db.get(user_email, {}).get('password') == password

@app.route('/change-email', methods=['POST'])
def change_email():
    data = request.json
    old_email = data.get('old_email')
    new_email = data.get('new_email')
    confirm_password = data.get('confirm_password')

    if not (old_email and new_email and confirm_password):
        return jsonify({'error': 'Missing required fields'}), 400

    if old_email not in users_db:
        return jsonify({'error': 'Old email does not exist'}), 400

    if not check_password(old_email, confirm_password):
        return jsonify({'error': 'Incorrect password'}), 401

    user = users_db[old_email]
    user['email'] = new_email
    users_db[new_email] = user
    del users_db[old_email]

    return jsonify({'message': 'Email updated successfully', 'new_email': new_email}), 200

if __name__ == '__main__':
    app.run(debug=True)