from flask import Flask, request

app = Flask(__name__)

def get_username_and_password():
    return request.args.get('username'), request.args.get('password')

def is_valid_credentials(username, password):
    # Replace with your actual credential checking logic
    valid_users = {
        'user1': 'password123',
        'admin': 'securepass'
    }
    return valid_users.get(username) == password

@app.route('/check_mod')
def check_mod():
    username, password = get_username_and_password()
    if is_valid_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)