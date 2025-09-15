from flask import Flask, render_template, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(message):
    # This is a placeholder for the actual database insertion logic
    print(f"Inserting message into database: {message}")

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        user_message = request.form.get('user_message')
        insert_user_message_in_db(user_message)
        return redirect('/')
    return render_template('main.html')

if __name__ == '__main__':
    app.run(debug=True)




