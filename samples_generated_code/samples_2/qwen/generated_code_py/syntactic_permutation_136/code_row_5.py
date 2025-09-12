from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    user = request.args.get('user')
    password = request.args.get('password')
    if user == 'correct_user' and password == 'correct_password':
        return 'true'
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)