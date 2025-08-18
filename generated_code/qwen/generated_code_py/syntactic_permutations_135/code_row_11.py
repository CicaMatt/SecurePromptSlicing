from flask import Flask, request

app = Flask(__name__)

# Dummy data for demonstration purposes
MOD_USERNAME = "admin"
MOD_PASSWORD = "password123"

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == MOD_USERNAME and password == MOD_PASSWORD:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)