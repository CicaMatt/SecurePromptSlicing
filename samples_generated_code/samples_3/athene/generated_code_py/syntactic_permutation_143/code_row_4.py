from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulated database of subscribed users
subscribed_users = ["user1@example.com", "user2@example.com", "user3@example.com"]

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if email in subscribed_users:
        subscribed_users.remove(email)
        return jsonify({"message": f"User {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": f"User {email} is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)