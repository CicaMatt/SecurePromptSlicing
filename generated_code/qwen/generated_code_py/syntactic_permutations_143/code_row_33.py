from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulated database of subscribed users
subscribed_users = {
    "user1@example.com": True,
    "user2@example.com": True,
    "user3@example.com": True
}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400
    
    if email in subscribed_users:
        del subscribed_users[email]
        return jsonify({"message": f"User {email} has been unsubscribed from the mailing list."}), 200
    else:
        return jsonify({"message": f"User {email} is not subscribed to the mailing list."}), 404

if __name__ == '__main__':
    app.run(debug=True)