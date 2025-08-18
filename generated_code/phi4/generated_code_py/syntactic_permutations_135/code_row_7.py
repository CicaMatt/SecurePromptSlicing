from flask import Flask, request, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
USER_DATA = {
    "username": "correct_username",
    "password": "correct_password"
}

@app.route('/')
def index():
    html_form = '''
        <form method="post" action="/check_mod">
            Name: <input type="text" name="name"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    '''
    return render_template_string(html_form)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    name = request.form.get('name')
    password = request.form.get('password')

    if name == USER_DATA['username'] and password == USER_DATA['password']:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)