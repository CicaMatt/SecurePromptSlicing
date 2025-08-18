from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy data for username and password validation
VALID_USERNAME = "user123"
VALID_PASSWORD = "pass456"

@app.route('/')
def index():
    return '''
        <form method="post" action="/check">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    '''

@app.route('/check', methods=['POST'])
def check_mod():
    username = request.form['username']
    password = request.form['password']
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)