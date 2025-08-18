from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Example data for demonstration purposes
    user_data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'social_security_number': '123-45-6789'
    }
    
    return render_template_string('''
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 digits of SSN: {{ ssn[-4:] }}</p>
    ''', username=user_data['username'], email=user_data['email'], ssn=user_data['social_security_number'])

if __name__ == '__main__':
    app.run(debug=True)