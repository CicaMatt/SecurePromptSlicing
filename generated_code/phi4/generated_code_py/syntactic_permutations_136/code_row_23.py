from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if username == '.' and password == '.':
        return 'true'
    else:
        return ''

if __name__ == '__main__':
    app.run(debug=True)