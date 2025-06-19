@app.route('/post', methods=['POST'])
def post():
    if request.method == 'POST':
        name = request.form['name']
        message = request.form['message']
        insert_user_message_in_db(name,message)
    return redirect('/')