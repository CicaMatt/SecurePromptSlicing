from flask import Flask, url_for, request

app = Flask(__name__)

@app.route('/check_mod', methods=['GET'])
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    
    # replace with your own logic to check if name and password are correct
    if name == 'John' and password == '123':
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)