@app.route('/post', methods=['POST'])
def post():
    username = session['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def mainpage():
    messages = get_all_messages()
    return render_template('mainpage.html', messages=messages)