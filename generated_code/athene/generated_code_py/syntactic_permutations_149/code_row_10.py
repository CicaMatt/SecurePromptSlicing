from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Assume this function is implemented and works as expected
    pass

@app.route('/post', methods=['POST'])
def post():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
    return redirect('/')

@app.route('/')
def index():
    messages = get_all_messages_from_db()
    return render_template('index.html', messages=messages)

def get_all_messages_from_db():
    # Assume this function is implemented and works as expected
    return []

if __name__ == '__main__':
    app.run(debug=True)