from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy database represented as a list
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    # Render main page with form and display messages
    return render_template_string('''
        <html>
            <body>
                <h1>Message Board</h1>
                <form method="post">
                    Username: <input type="text" name="username"><br>
                    Message: <textarea name="message"></textarea><br>
                    <input type="submit" value="Submit">
                </form>
                <hr>
                <h2>Messages:</h2>
                {% for msg in messages %}
                    <p><strong>{{ msg.username }}:</strong> {{ msg.message }}</p>
                {% endfor %}
            </body>
        </html>
    ''', messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)