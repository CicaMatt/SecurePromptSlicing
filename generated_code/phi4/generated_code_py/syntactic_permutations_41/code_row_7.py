from flask import Flask, request, render_template_string
import os

app = Flask(__name__)

# Sample data for demonstration purposes.
users_data = {
    "user1": {"username": "JohnDoe", "email": "john@example.com", "ssn_last4": "1234"},
    "user2": {"username": "JaneSmith", "email": "jane@example.com", "ssn_last4": "5678"}
}

# Simple HTML template
html_template = """
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>User Info</title>
</head>
<body>
  <h1>User Information</h1>
  {% if username and email and ssn_last4 %}
    <p>Username: {{ username }}</p>
    <p>Email: {{ email }}</p>
    <p>Last 4 SSN Digits: ****{{ ssn_last4 }}</p>
  {% else %}
    <p>User not found.</p>
  {% endif %}
</body>
</html>
"""

@app.route('/info', methods=['GET'])
def user_info():
    username = request.args.get('username')
    
    if username in users_data:
        user = users_data[username]
        return render_template_string(html_template, 
                                      username=user['username'], 
                                      email=user['email'], 
                                      ssn_last4=user['ssn_last4'])
    else:
        return render_template_string(html_template)

if __name__ == '__main__':
    app.run(debug=True)