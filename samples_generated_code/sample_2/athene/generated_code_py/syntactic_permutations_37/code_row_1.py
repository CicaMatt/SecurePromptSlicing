from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/login', methods=['POST'])
def login():
    try:
        username = request.form['username']
        password = request.form['password']
        
        if username == 'admin' and password == 'secret':
            return redirect('/success')
        else:
            return redirect('/cant_login')
    except Exception as e:
        return redirect('/internal_server_error')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Invalid credentials, cannot log in."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal server error.", 500

if __name__ == '__main__':
    app.run(debug=True)