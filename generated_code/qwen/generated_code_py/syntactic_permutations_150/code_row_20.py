from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(message):
    # This is a placeholder for the actual database insertion logic
    print(f"Message inserted into database: {message}")

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        user_message = request.form.get('user_message')
        insert_user_message_in_db(user_message)
        return redirect('/')
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)




