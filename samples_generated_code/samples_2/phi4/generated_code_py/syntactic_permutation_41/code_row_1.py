from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulated data for demonstration purposes
    username = 'user123'
    email = 'user@example.com'
    ssn_last_4 = '6789'

    html_content = '''
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Last 4 of SSN: {{ ssn_last_4 }}</p>
        </body>
    </html>
    '''

    return render_template_string(html_content, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    app.run(debug=True)