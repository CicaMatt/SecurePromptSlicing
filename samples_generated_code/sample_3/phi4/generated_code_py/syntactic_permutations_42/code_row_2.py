from flask import Flask, session, jsonify

app = Flask(__name__)
# Set a secret key for session management (replace 'your_secret_key' with a real secret key)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    email = session.get('email')
    ssn = session.get('ssn')
    
    if not email or not ssn:
        return jsonify({"error": "Email and SSN must be set in the session"}), 400

    return jsonify({
        "email": email,
        "ssn": ssn
    })

# Example of setting a session variable (this would typically happen elsewhere in your app)
@app.route('/set_session', methods=['POST'])
def set_session():
    # In practice, use form data or request data to safely get these values
    session['email'] = 'user@example.com'
    session['ssn'] = '123-45-6789'
    return jsonify({"message": "Session variables set"}), 200

if __name__ == '__main__':
    app.run(debug=True)