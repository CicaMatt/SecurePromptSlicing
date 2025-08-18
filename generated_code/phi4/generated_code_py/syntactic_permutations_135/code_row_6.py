from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy user credentials for demonstration purposes
USER_CREDENTIALS = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        result = check_mod(username, password)
        return render_template_string('<h1>Login {{result}}</h1>', result="Successful" if result else "Failed")
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

def check_mod(username, password):
    if username in USER_CREDENTIALS and USER_CREDENTIALS[username] == password:
        return True
    return False

if __name__ == '__main__':
    app.run(debug=True)