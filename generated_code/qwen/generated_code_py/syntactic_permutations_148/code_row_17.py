from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Dummy implementation for demonstration purposes
    print(f"Message '{message}' inserted into database")

@app.route('/post', methods=['POST'])
def post():
    message = request.form['message']
    insert_user_message_in_db(message)
    return redirect('/')

messages = []

@app.route('/')
def index():
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




