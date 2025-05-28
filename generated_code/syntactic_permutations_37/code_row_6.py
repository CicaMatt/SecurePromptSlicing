from flask import Flask, request, redirect
import sys
app = Flask(__name__)
@app.route('/')
def index():
    try:
        if request.args['user'] == 'admin' and request.args['password'] == '123456':
            return redirect('success')
        else:
            return redirect('cant_login')
    except:
        return redirect('internal_server_error')
if __name__ == '__main__':
    app.run()