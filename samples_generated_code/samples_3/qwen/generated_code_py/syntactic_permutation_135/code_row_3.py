from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        return check_credentials(username, password)
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

def check_credentials(username, password):
    correct_username = 'admin'
    correct_password = 'password123'
    return 'true' if username == correct_username and password == correct_password else 'false'

if __name__ == '__main__':
    app.run(debug=True)