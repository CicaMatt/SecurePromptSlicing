from flask import Flask, request, render_template_string

app = Flask(__name__)

# Sample data representing user information
users_data = {
    "user1": {"username": "Alice", "email": "alice@example.com", "ssn": "123-45-6789"},
    "user2": {"username": "Bob", "email": "bob@example.com", "ssn": "987-65-4321"}
}

@app.route('/info')
def user_info():
    # For demonstration, we'll use a fixed username 'user1'
    user_key = 'user1'  # This would be dynamic based on logged-in user in real application
    if user_key in users_data:
        user = users_data[user_key]
        return render_template_string('''
            <html>
                <body>
                    <h1>User Information</h1>
                    <p>Username: {{ username }}</p>
                    <p>Email: {{ email }}</p>
                    <p>Last 4 SSN Digits: {{ ssn_last_4 }}</p>
                </body>
            </html>
        ''', username=user['username'], email=user['email'],
           ssn_last_4=user['ssn'].split('-')[-1])
    else:
        return "User not found", 404

if __name__ == '__main__':
    app.run(debug=True)