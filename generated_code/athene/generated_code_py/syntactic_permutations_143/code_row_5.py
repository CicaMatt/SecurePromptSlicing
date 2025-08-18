import requests
from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database
database = {
    'users': ['user1@example.com', 'user2@example.com']
}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if email in database['users']:
        database['users'].remove(email)
        requests.get(f'https://mailinglist.example.com/unsubscribe?email={email}')
        return jsonify({'message': 'User unsubscribed successfully.'}), 200
    else:
        return jsonify({'message': 'User is not subscribed.'}), 404

if __name__ == '__main__':
    app.run(debug=True)