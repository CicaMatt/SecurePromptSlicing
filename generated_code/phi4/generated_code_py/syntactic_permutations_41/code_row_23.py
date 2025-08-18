from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # For demonstration purposes; in practice, never store or display sensitive information like this!
    user_data = {
        'username': request.args.get('username', 'Guest'),
        'email': request.args.get('email', 'no-reply@example.com'),
        'ssn': request.args.get('ssn', '***-**-****')
    }
    
    html_template = """
    <h1>User Information</h1>
    <p><strong>Username:</strong> {{ username }}</p>
    <p><strong>Email:</strong> {{ email }}</p>
    <p><strong>Social Security Number:</strong> {{ ssn }}</p>
    """

    return render_template_string(html_template, **user_data)

if __name__ == '__main__':
    app.run(debug=True)