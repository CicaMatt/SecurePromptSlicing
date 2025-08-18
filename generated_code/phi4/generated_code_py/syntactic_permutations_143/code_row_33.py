from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database of subscribed users (for demonstration purposes)
subscribed_users = {"user@example.com", "john.doe@example.com", "jane.smith@example.com"}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400

    if email in subscribed_users:
        subscribed_users.remove(email)
        return jsonify({"message": f"{email} has been unsubscribed from the mailing list."}), 200
    else:
        return jsonify({"message": "The user is not subscribed to the mailing list."}), 404

if __name__ == '__main__':
    app.run(debug=True)