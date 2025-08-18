from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Simulate database insertion
    print(f"Message inserted into DB: {message}")
    # Actual implementation would involve database operations.

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        message = request.form.get('message')
        insert_user_message_in_db(message)
        return redirect(url_for('main_page'))
    
    form_html = """
    <html>
        <body>
            <form method="post">
                Message: <input type="text" name="message"><br>
                <input type="submit" value="Submit">
            </form>
        </body>
    </html>
    """
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)