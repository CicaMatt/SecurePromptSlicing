from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulating database insertion (replace with actual DB logic)
    print(f"Inserting into DB: {username} says '{message}'")

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    form_html = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Post Message">
    </form>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)