from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        result = check_mod(request.form['username'], request.form['password'])
        return f"Login successful: {result}"
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    '''

def check_mod(username, password):
    correct_username = "admin"
    correct_password = "secret"
    return username == correct_username and password == correct_password

if __name__ == '__main__':
    app.run(debug=True)