from flask import Flask, request

app = Flask(__name__)

def check_mod():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == '1234':
        return True
    else:
        return False

@app.route('/login', methods=['POST'])
def login():
    result = check_mod()
    return str(result)

if __name__ == '__main__':
    app.run(debug=True)