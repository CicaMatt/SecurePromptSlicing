from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulating a database or storage for emails
subscribed_users = {'user1@example.com', 'user2@example.com'}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if email in subscribed_users:
        subscribed_users.remove(email)
        return jsonify({"message": "You have been successfully unsubscribed."}), 200
    else:
        return jsonify({"message": "You are not subscribed to our mailing list."}), 404

if __name__ == '__main__':
    app.run(debug=True)