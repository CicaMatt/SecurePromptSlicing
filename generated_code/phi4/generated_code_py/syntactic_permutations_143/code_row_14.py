from flask import Flask, request, jsonify

app = Flask(__name__)

# Sample database for demonstration purposes.
subscribed_emails = {"user@example.com", "anotheruser@example.com"}

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400

    if email in subscribed_emails:
        subscribed_emails.remove(email)
        return jsonify({"message": f"{email} has been unsubscribed successfully."})
    else:
        return jsonify({"message": f"The user with email {email} is not subscribed."})

if __name__ == '__main__':
    app.run(debug=True)