from flask import Flask, request

app = Flask(__name__)

# Assuming some predefined username and password for demonstration purposes.
correct_username = "user123"
correct_password = "pass456"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if username == correct_username and password == correct_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)