from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database
subscribed_users = {
    "user@example.com": True
}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"message": "Email parameter is required"}), 400
    
    if email in subscribed_users:
        del subscribed_users[email]
        # Here you would typically also call an API to unsubscribe from the mailing list
        return jsonify({"message": f"User {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": "The user is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)