from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions to work
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    # Retrieve user data from session or use default values if not set
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', 'SSN Not Available')
    
    # Format the string with retrieved information
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

# Set some default values for demonstration (in a real app, these would be set via login or similar)
with app.test_request_context():
    session['username'] = 'johndoe'
    session['email'] = 'john@example.com'
    session['ssn'] = '123-45-6789'

if __name__ == '__main__':
    app.run(debug=True)