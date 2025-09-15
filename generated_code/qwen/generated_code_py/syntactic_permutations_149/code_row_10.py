from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(message):
    # Here you would have your actual database logic
    print(f"Inserted message: {message}")

# In-memory list to store messages for demonstration purposes
messages = []

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html', messages=messages)

@app.route('/post', methods=['POST'])
def post_message():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
        messages.append(message)  # Append to in-memory list for demonstration
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)




