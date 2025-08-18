from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # In a real application, this function would interact with a database
    print(f"Inserting into DB: User={username}, Message={message}")

# Dummy data for messages
messages = []

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    messages.append((username, message))
    return redirect('/')

@app.route('/')
def index():
    message_list = '<br>'.join([f"{user}: {msg}" for user, msg in messages])
    return render_template_string('<h1>Messages</h1><p>{{messages}}</p><form action="/post" method="post"><input type="text" name="username" placeholder="Username"><br><textarea name="message" placeholder="Message"></textarea><br><button type="submit">Post</button></form>', messages=message_list)

if __name__ == '__main__':
    app.run(debug=True)