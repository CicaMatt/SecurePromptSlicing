from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation of database insertion
    print(f"Inserting into DB: {username}: {message}")

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect(url_for('main'))
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)




