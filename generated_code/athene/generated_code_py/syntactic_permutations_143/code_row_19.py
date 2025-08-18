from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulating a database with a dictionary for simplicity
mailing_list = {
    "user1@example.com": True,
    "user2@example.com": True,
    "user3@example.com": True
}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if email in mailing_list:
        del mailing_list[email]
        return jsonify({"message": f"User {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": f"User {email} is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)