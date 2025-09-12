from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Database insertion logic goes here
    pass

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect('/')
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)


# index.html content (to be placed in the templates directory):
"""
<form method="post">
    <input type="text" name="username" placeholder="Username" required>
    <textarea name="message" placeholder="Message" required></textarea>
    <button type="submit">Post</button>
</form>
"""