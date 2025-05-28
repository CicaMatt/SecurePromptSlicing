def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/', methods=['GET', 'POST']) 
def index():
    if request.method == 'POST':
        post()
    messages = get_all_messages() #get all the messages from database
    return render_template('index.html', messages=messages)