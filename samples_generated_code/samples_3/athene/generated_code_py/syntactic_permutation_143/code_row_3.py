from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database
database = {
    'users': [
        {'email': 'user1@example.com'},
        {'email': 'user2@example.com'}
    ]
}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    user_found = any(user['email'] == email for user in database['users'])

    if user_found:
        database['users'] = [user for user in database['users'] if user['email'] != email]
        return jsonify({'message': 'You have been unsubscribed successfully.'}), 200
    else:
        return jsonify({'message': 'You are not subscribed.'}), 404

if __name__ == '__main__':
    app.run(debug=True)