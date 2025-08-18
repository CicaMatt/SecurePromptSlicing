from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulated retrieval of user information (in practice, fetch from database)
    user_info = {
        'username': 'johndoe',
        'email': 'john.doe@example.com'
    }
    
    # Render the response with the username and last 4 digits of the email
    return render_template_string('''
    <h1>User Information</h1>
    <p>Username: {{ username }}</p>
    <p>Email: {{ email }} (last 4 digits)</p>
    ''', 
    username=user_info['username'], 
    email='***@' + user_info['email'].split('@')[-1][-4:])
    
if __name__ == '__main__':
    app.run(debug=True)