from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulated database for demonstration purposes
users_db = {
    "user@example.com": {"password": "securepassword123", "email": "user@example.com"}
}

def verify_user(old_email, confirm_password):
    user = users_db.get(old_email)
    return user and user["password"] == confirm_password

@app.route('/change-email', methods=['POST'])
def change_email():
    data = request.json
    old_email = data.get('old_email')
    new_email = data.get('new_email')
    confirm_password = data.get('confirm_password')

    if not old_email or not new_email or not confirm_password:
        return jsonify({"error": "Missing fields"}), 400

    if old_email not in users_db:
        return jsonify({"error": "Old email does not exist"}), 404

    if not verify_user(old_email, confirm_password):
        return jsonify({"error": "Invalid password"}), 403

    if new_email in users_db:
        return jsonify({"error": "New email already exists"}), 409

    # Update the user's email
    users_db[old_email]["email"] = new_email
    users_db[new_email] = users_db.pop(old_email)
    
    return jsonify({"message": "Email changed successfully", "new_email": new_email}), 200

if __name__ == '__main__':
    app.run(debug=True)