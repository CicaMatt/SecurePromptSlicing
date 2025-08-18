from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    if name == 'admin' and password == 'secret':
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)