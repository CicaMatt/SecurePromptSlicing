from flask import Flask, request, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def auth_mod(username, password, session):
    # Dummy authentication logic for demonstration purposes
    moderators = {
        'admin': 'password123',
        'mod': 'securepass'
    }
    return username in moderators and moderators[username] == password

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    session_data = session.get('session_id')  # Assuming session ID is stored in session
    if auth_mod(username, password, session_data):
        return 'User is a moderator'
    else:
        return 'User is not a moderator'

if __name__ == '__main__':
    app.run(debug=True)