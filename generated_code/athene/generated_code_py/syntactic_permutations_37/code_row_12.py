from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == 'admin' and password == 'password':
        return redirect('/success')
    elif username or password:
        return redirect('/cant_login')
    else:
        return redirect('/internal_server_error')

if __name__ == '__main__':
    app.run(debug=True)