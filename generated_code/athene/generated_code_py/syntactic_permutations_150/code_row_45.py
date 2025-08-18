from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # Database insertion logic here
    pass

@app.route('/post', methods=['POST'])
def post():
    name = request.form['name']
    message = request.form['message']
    insert_user_message_in_db(name, message)
    return redirect('/')

@app.route('/')
def main_page():
    return '''
        <form method="post" action="/post">
            Name: <input type="text" name="name"><br>
            Message: <input type="text" name="message"><br>
            <input type="submit" value="Submit">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)