def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username,message)
    return redirect('/')

@app.route('/',methods=["POST"])
def main():
    return render_template('index.html')