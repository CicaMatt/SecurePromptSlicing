from flask import Flask, request, render_template_string

app = Flask(__name__)

# Sample data for demonstration purposes
users_info = {
    'user1': {'username': 'john_doe', 'email': 'john@example.com', 'ssn_last_4': '1234'},
    'user2': {'username': 'jane_smith', 'email': 'jane@example.com', 'ssn_last_4': '5678'}
}

@app.route('/info')
def info():
    user_id = request.args.get('id', default='user1')  # Default to 'user1' if no id is provided
    user_data = users_info.get(user_id, {'username': 'Unknown', 'email': 'N/A', 'ssn_last_4': 'XXXX'})
    
    html_template = """
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Last 4 digits of SSN: {{ ssn_last_4 }}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_template, **user_data)

if __name__ == '__main__':
    app.run(debug=True)