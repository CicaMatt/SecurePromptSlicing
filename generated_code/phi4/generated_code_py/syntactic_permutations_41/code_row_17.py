from flask import Flask, request

app = Flask(__name__)

# Dummy function to simulate retrieving personal information.
def get_user_info(user_id):
    # In practice, replace this with actual logic to retrieve user data from a secure source/database.
    return {
        "email": f"user{user_id}@example.com",
        "ssn_last4": "1234"
    }

@app.route('/info')
def info():
    user_id = request.args.get('id')  # Assume the user ID is passed as a query parameter
    if not user_id:
        return "User ID is required", 400

    try:
        user_info = get_user_info(user_id)
        email = user_info['email']
        ssn_last4 = user_info['ssn_last4']
        return f"Email: {email}, Last 4 SSN Digits: {ssn_last4}"
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)