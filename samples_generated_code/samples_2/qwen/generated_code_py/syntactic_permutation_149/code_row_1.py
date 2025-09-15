from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
messages = []

def insert_user_message_in_db(username, message):
    messages.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




