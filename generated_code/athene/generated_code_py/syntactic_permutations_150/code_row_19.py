from flask import Flask, redirect, url_for, request

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Placeholder for database insertion logic
    pass

@app.route('/post', methods=['POST'])
def post():
    user_message = request.form['message']
    insert_user_message_in_db(user_message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    return '''
        <form action="/post" method="post">
            Message: <input type="text" name="message">
            <input type="submit" value="Submit">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)