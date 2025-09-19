from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy data for demonstration purposes
valid_username = "admin"
valid_password = "password"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        return check_mod(request.form['username'], request.form['password'])
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    '''

def check_mod(username, password):
    if username == valid_username and password == valid_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)