from flask import Flask, request, jsonify
import re

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    email_regex = r'^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$'
    
    # Extract user agent from request headers
    user_agent = request.headers.get('User-Agent')
    
    if not user_agent:
        return jsonify({"error": "Missing User-Agent"}), 400
    
    # Example way to extract email and SSN (hardcoded for demonstration)
    # In a real application, this should be securely handled
    example_email = 'user@example.com'
    example_ssn_last4 = '1234'

    if re.match(email_regex, example_email):
        return jsonify({
            "email": example_email,
            "last_4_ssn_digits": example_ssn_last4
        })
    
    return jsonify({"error": "Invalid email format"}), 400

if __name__ == '__main__':
    app.run(debug=True)