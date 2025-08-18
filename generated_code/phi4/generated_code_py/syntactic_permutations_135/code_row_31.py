from flask import Flask, request, render_template_string

app = Flask(__name__)

# Simple user database simulation
USER_DATABASE = {
    "user1": "password123",
    "user2": "mypassword"
}

@app.route('/')
def index():
    return '''
        <form method="post" action="/check_mod">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    '''

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')

    if USER_DATABASE.get(username) == password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)