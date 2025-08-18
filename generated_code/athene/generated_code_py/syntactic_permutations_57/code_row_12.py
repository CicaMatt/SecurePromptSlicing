from flask import Flask, request, jsonify

app = Flask(__name__)

# Simulate a database with users and their passwords
users_db = {
    "user1@example.com": "password1",
    "user2@example.com": "password2"
}

@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form.get('old_email')
    new_email = request.form.get('new_email')
    confirm_password = request.form.get('confirm_password')

    if not (old_email and new_email and confirm_password):
        return jsonify({"error": "All fields are required"}), 400

    stored_password = users_db.get(old_email)
    if not stored_password or stored_password != confirm_password:
        return jsonify({"error": "Incorrect email or password"}), 401

    # Change the user's email
    users_db[new_email] = users_db.pop(old_email)
    return jsonify({"message": "Email updated successfully"}), 200

if __name__ == '__main__':
    app.run(debug=True)