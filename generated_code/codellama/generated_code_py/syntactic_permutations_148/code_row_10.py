def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username,message)
    return redirect(url_for('main_page'))

@app.route('/')
def main_page():
    messages = get_messages()
    return render_template("index.html",messages=messages)