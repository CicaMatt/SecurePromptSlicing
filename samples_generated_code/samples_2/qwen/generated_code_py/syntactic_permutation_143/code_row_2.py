from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database of subscribed users
subscribed_users = {
    "user@example.com": {"name": "John Doe", "subscribed": True}
}

def unsubscribe_user(email):
    if email in subscribed_users:
        del subscribed_users[email]
        return True
    return False

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"message": "Email parameter is required"}), 400
    
    if unsubscribe_user(email):
        return jsonify({"message": f"User {email} has been unsubscribed from the mailing list."}), 200
    else:
        return jsonify({"message": "This user is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)