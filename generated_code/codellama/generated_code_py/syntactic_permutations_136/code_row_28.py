from flask import Flask, request, redirect, url_for
app = Flask(__name__)

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if username == 'admin' and password == 'pass':
        return 'true'

if __name__ == '__main__':
    app.run()