def insert_user_message_in_db(username, message):
        # Code to insert data into database goes here
        pass


    @app.route('/', methods=['GET', 'POST'])
    def main():
        if request.method == 'POST':
            username = request.form['username']
            message = request.form['message']
            insert_user_message_in_db(username, message)
            return redirect('/')
        else:
            # Code to fetch messages from database goes here
            messages = []
            return render_template('main.html', messages=messages)