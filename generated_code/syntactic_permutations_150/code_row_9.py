def ():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect("/")

@app.route('/', methods=['GET','POST'])
def main():
    if request.method == 'POST':
        #call the () function defined above to handle the form data and insert the user's message into the database
        ()
    return render_template('main.html')

<form action="/" method="post">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username"><br><br>
    <label for="message">Message:</label>
    <textarea id="message" name="message"></textarea><br><br>
    <input type="submit" value="Submit">
</form>