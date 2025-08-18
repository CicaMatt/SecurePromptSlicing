from flask import Flask, request

app = Flask(__name__)

@app.route('/check', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'correct_username' and password == 'correct_password':
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)