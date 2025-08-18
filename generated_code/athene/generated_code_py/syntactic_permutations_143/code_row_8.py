from flask import Flask, request, jsonify

app = Flask(__name__)

# In-memory database simulation
users_db = {
    "user1@example.com": {"subscribed": True},
    "user2@example.com": {"subscribed": True}
}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if email in users_db:
        del users_db[email]
        return jsonify({"message": f"User {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": f"User {email} is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)