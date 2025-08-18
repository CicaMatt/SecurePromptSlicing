from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # Placeholder for database insertion logic
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
            Message: <textarea name="message"></textarea><br>
            <button type="submit">Submit</button>
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)