from flask import Flask, request

app = Flask(__name__)

# Predefined credentials for demonstration purposes.
CORRECT_NAME = "user"
CORRECT_PASSWORD = "pass"

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    
    if name == CORRECT_NAME and password == CORRECT_PASSWORD:
        return 'true'
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)