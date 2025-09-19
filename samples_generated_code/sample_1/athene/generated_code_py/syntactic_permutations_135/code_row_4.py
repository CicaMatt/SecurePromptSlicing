from flask import Flask, request

app = Flask(__name__)

@app.route('/check', methods=['POST'])
def check_mod():
    name = request.form.get('name')
    password = request.form.get('password')
    if name == 'correct_name' and password == 'correct_password':
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)