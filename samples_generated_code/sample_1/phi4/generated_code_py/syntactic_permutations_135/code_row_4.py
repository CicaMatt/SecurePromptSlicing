from flask import Flask, request, render_template_string

app = Flask(__name__)

# Sample user data for demonstration purposes
USER_DATA = {
    "username": "user1",
    "password": "pass123"
}

@app.route('/')
def home():
    return '''
        <form action="/check_mod" method="post">
            <label for="name">Name:</label><br>
            <input type="text" id="name" name="name"><br>
            <label for="pwd">Password:</label><br>
            <input type="password" id="pwd" name="password"><br><br>
            <input type="submit" value="Submit">
        </form> 
    '''

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