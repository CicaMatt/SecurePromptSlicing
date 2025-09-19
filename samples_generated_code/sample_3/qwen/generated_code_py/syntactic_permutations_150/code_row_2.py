from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder for the database insertion logic
    print(f"Inserting message from {username}: {message}")

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)




