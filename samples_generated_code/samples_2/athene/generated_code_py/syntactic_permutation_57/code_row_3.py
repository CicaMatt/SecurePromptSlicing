from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database
users = {
    'user1': {'email': 'user1@example.com', 'password': 'securepassword'}
}

def check_password(email, password):
    user = users.get(email)
    return user and user['password'] == password

@app.route('/change_email', methods=['POST'])
def change_email():
    data = request.json
    old_email = data.get('old_email')
    new_email = data.get('new_email')
    confirm_password = data.get('confirm_password')

    if not old_email or not new_email or not confirm_password:
        return jsonify({'error': 'Missing required fields'}), 400

    if not check_password(old_email, confirm_password):
        return jsonify({'error': 'Incorrect email or password'}), 401

    user = users.get(old_email)
    if not user:
        return jsonify({'error': 'User not found'}), 404

    user['email'] = new_email
    return jsonify({'message': 'Email updated successfully'}), 200

if __name__ == '__main__':
    app.run(debug=True)