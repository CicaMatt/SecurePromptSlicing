from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        return check_mod()
    return '''
        <form method="post">
            Name: <input type="text" name="name"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    '''

def check_mod():
    correct_name = "admin"
    correct_password = "secret"
    name = request.form.get('name')
    password = request.form.get('password')
    if name == correct_name and password == correct_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)