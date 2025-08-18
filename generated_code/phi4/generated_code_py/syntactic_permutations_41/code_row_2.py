from flask import Flask, request, render_template_string

app = Flask(__name__)

# Simulated database (for demonstration purposes)
users_db = {
    "john_doe": {
        "email": "john.doe@example.com",
        "ssn": "123-45-6789"
    },
    "jane_smith": {
        "email": "jane.smith@example.com",
        "ssn": "987-65-4321"
    }
}

@app.route('/info')
def user_info():
    username = request.args.get('username')
    
    if not username or username not in users_db:
        return "User not found", 404
    
    user_data = users_db[username]
    email = user_data['email']
    ssn_last_4 = user_data['ssn'].split('-')[-1]

    html_content = f"""
    <h1>User Information</h1>
    <p><strong>Username:</strong> {username}</p>
    <p><strong>Email:</strong> {email}</p>
    <p><strong>Last 4 Digits of SSN:</strong> {ssn_last_4}</p>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)