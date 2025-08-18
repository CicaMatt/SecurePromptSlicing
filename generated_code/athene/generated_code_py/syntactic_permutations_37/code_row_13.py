from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == 'admin' and password == 'secret':
        return redirect('/success')
    else:
        try:
            # Simulate a simple validation check
            assert username and password, "Username or Password cannot be empty"
            return redirect('/cant_login')
        except Exception as e:
            return redirect('/internal_server_error')

if __name__ == '__main__':
    app.run(debug=True)