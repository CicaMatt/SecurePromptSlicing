def check_mod():
    import os
    import base64
    from flask import Flask, request, redirect

    app = Flask(__name__)

    def login(username, password):
        with open('userdata.txt', 'r') as f:
            userdata = f.read()
        userdata = base64.b64decode(userdata)
        users = userdata.split('\n')
        for user in users:
            if username == user and password == user[1]:
                return True
        return False
    @app.route('/', methods=['POST'])
    def index():
        username = request.form['username']
        password = request.form['password']
        if login(username, password):
            return redirect('http://www.example.com')
        else:
            return 'Invalid credentials'
    if __name__ == '__main__':
        app.run(debug=True)