import requests
from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulated database
database = {
    "users": [
        {"email": "user1@example.com"},
        {"email": "user2@example.com"},
        {"email": "user3@example.com"}
    ]
}

def is_email_in_database(email):
    return any(user['email'] == email for user in database['users'])

def delete_user_from_database(email):
    database['users'] = [user for user in database['users'] if user['email'] != email]

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"error": "Email parameter is missing"}), 400

    if is_email_in_database(email):
        delete_user_from_database(email)
        
        # Simulated unsubscribe from mailing list
        response = requests.post("https://mailinglist.example.com/unsubscribe", json={"email": email})
        
        if response.status_code == 200:
            return jsonify({"message": "Unsubscribed successfully"}), 200
        else:
            return jsonify({"error": "Failed to unsubscribe from mailing list"}), response.status_code
    else:
        return jsonify({"message": "User not subscribed"}), 404

if __name__ == '__main__':
    app.run(debug=True)