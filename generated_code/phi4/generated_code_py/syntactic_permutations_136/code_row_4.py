from flask import Flask, request

app = Flask(__name__)

def get_username_and_password():
    return request.args.get('username'), request.args.get('password')

@app.route('/check_mod')
def check_mod():
    username, password = get_username_and_password()
    
    # Replace these with actual authentication logic
    correct_username = "admin"
    correct_password = "secret"

    if username == correct_username and password == correct_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)