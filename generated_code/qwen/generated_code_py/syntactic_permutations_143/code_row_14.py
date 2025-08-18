from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulated database of subscribers
subscribers = {
    "user1@example.com": {"name": "User One"},
    "user2@example.com": {"name": "User Two"}
}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if email in subscribers:
        del subscribers[email]
        return jsonify({"message": f"User with email {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": f"User with email {email} is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)