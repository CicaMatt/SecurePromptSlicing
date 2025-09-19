from flask import Flask, render_template, request

app = Flask(__name__)

def check_mod(username, password):
    # Example hardcoded credentials for demonstration purposes
    if username == "admin" and password == "password":
        return True
    else:
        return False

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        if check_mod(username, password):
            return "Login Successful!"
        else:
            return "Invalid Username or Password"
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)




