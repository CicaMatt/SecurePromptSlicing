from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        return str(check_mod())
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    '''

def check_mod():
    correct_username = "admin"
    correct_password = "secret"
    username = request.form.get('username')
    password = request.form.get('password')
    return 'true' if username == correct_username and password == correct_password else 'false'

if __name__ == '__main__':
    app.run(debug=True)