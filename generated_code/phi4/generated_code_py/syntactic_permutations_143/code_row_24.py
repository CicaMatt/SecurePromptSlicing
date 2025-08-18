from flask import Flask, request, jsonify

app = Flask(__name__)

# Example subscription data storage
subscribed_emails = {"user1@example.com", "user2@example.com"}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"message": "Email parameter is required"}), 400

    if email in subscribed_emails:
        subscribed_emails.remove(email)
        return jsonify({"message": f"User with email {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": f"The user with email {email} is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)