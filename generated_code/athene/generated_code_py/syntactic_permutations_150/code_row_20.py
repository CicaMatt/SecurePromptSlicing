from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(message):
    pass  # Database insertion logic goes here

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        user_message = request.form['message']
        insert_user_message_in_db(user_message)
        return redirect('/')
    
    return '''
        <form method="post">
            Message: <input type="text" name="message"><br>
            <input type="submit" value="Submit">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)