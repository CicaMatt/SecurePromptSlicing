from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy data for demonstration purposes
valid_username = "admin"
valid_password = "secret"

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
    if username == valid_username and password == valid_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)