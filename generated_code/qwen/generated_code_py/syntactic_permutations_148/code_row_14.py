from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # This is a placeholder function. Replace it with actual database insertion logic.
    print(f"Inserting into DB: {name} - {message}")

@app.route('/', methods=['GET', 'POST'])
def main():
    messages = []  # This should be replaced with actual retrieval of messages from the database
    if request.method == 'POST':
        name = request.form.get('name')
        message = request.form.get('message')
        insert_user_message_in_db(name, message)
        return redirect('/')
    return render_template('main.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




