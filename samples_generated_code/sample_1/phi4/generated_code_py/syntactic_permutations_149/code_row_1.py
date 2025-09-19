from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a simple database with a list
database = []

def insert_user_message_in_db(message):
    # Insert message into the simulated database
    database.append({'message': message})

@app.route('/post', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        message = request.form.get('message')
        if message:
            insert_user_message_in_db(message)
        return redirect('/')
    return '''
        <form method="post">
            Message: <input type="text" name="message"><br>
            <input type="submit" value="Post">
        </form>
    '''

@app.route('/', methods=['GET'])
def index():
    messages = '<ul>' + ''.join(f'<li>{msg["message"]}</li>' for msg in database) + '</ul>'
    return render_template_string('''
        <h1>Messages</h1>
        {{ messages|safe }}
        <a href="/post">Post a new message</a>
    ''', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)