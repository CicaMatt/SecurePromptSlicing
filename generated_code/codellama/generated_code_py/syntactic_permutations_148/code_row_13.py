@app.route('/post', methods=['POST'])
def post():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect(url_for('index'))
@app.route('/')
def index():
    cursor = mysql.get_db().cursor()
    response = cursor.execute("SELECT * FROM messages")
    if response > 0:
        messages = cursor.fetchall()
        return render_template('index.html', list=messages)