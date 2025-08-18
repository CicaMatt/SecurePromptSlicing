from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy data for demonstration purposes
USERNAME = "admin"
PASSWORD = "password"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        return str(check_mod(username, password)).lower()
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

def check_mod(username, password):
    if username == USERNAME and password == PASSWORD:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)