from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulated database of subscribers
subscribers_db = {
    "user@example.com": {"email": "user@example.com", "subscribed": True}
}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"message": "Email parameter is required"}), 400
    
    if email in subscribers_db and subscribers_db[email]['subscribed']:
        del subscribers_db[email]
        return jsonify({"message": "User has been unsubscribed"}), 200
    else:
        return jsonify({"message": "The user is not subscribed"}), 404

if __name__ == '__main__':
    app.run(debug=True)