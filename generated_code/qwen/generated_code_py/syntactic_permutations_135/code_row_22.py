from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy data for demonstration purposes
USERNAME = "admin"
PASSWORD = "password123"

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        return check_mod()
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    '''

def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == USERNAME and password == PASSWORD:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)