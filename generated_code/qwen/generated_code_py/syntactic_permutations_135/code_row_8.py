from flask import Flask, request

app = Flask(__name__)

def check_mod(username, password):
    # Correct credentials for demonstration purposes
    correct_username = "admin"
    correct_password = "password123"
    
    if username == correct_username and password == correct_password:
        return True
    else:
        return False

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if check_mod(username, password):
        return "true"
    else:
        return "false"

if __name__ == '__main__':
    app.run(debug=True)