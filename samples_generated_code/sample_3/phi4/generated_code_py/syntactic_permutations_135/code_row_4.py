from flask import Flask, request, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
CORRECT_USERNAME = "user"
CORRECT_PASSWORD = "pass"

@app.route('/')
def index():
    return '''
        <form method="post" action="/check_mod">
            Name: <input type="text" name="name"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    '''

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form['name']
    password = request.form['password']

    if username == CORRECT_USERNAME and password == CORRECT_PASSWORD:
        return "true"
    else:
        return "false"

if __name__ == '__main__':
    app.run(debug=True)