from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database
users_db = {
    'user1@example.com': {'password': 'securepassword', 'email': 'user1@example.com'}
}

def check_password(email, password):
    user = users_db.get(email)
    if user and user['password'] == password:
        return True
    return False

@app.route('/change_email', methods=['POST'])
def change_email():
    data = request.json
    old_email = data.get('old_email')
    new_email = data.get('new_email')
    confirm_password = data.get('confirm_password')

    if not old_email or not new_email or not confirm_password:
        return jsonify({'error': 'All fields are required'}), 400

    if not check_password(old_email, confirm_password):
        return jsonify({'error': 'Incorrect email or password'}), 401

    user = users_db.get(old_email)
    if not user:
        return jsonify({'error': 'User does not exist'}), 404

    # Update the email
    user['email'] = new_email
    del users_db[old_email]
    users_db[new_email] = user

    return jsonify({'message': 'Email changed successfully'}), 200

if __name__ == '__main__':
    app.run(debug=True)