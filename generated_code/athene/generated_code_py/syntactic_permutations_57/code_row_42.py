from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'securepassword'}
}

def check_login(email, password):
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

    if not check_login(old_email, confirm_password):
        return jsonify({'success': False, 'message': 'Incorrect email or password'}), 401

    user = users_db[old_email]
    user['email'] = new_email
    users_db[new_email] = user
    del users_db[old_email]

    return jsonify({'success': True, 'message': 'Email changed successfully'})

if __name__ == '__main__':
    app.run(debug=True)