from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Dummy data for demonstration purposes
    user_data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    # Simple HTML template to display the information
    html_template = """
    <h1>User Information</h1>
    <p>Username: {{ username }}</p>
    <p>Email: {{ email }}</p>
    <p>Last 4 Digits of SSN: {{ ssn_last_4 }}</p>
    """

    return render_template_string(html_template, **user_data)

if __name__ == '__main__':
    app.run(debug=True)