from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        return str(check_mod()).lower()
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
    return username == 'admin' and password == 'secret'

if __name__ == '__main__':
    app.run(debug=True)