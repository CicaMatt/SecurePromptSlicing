import sqlite3

def post():
    # Get the message from the form
    msg = request.form['message']

    # Check if there is a file in the request
    if 'photo' in request.files:
        # Get the photo
        photo = request.files['photo']
        
        # Add the photo to the database
        insert_user_message_in_db(msg, photo)
    else:
        # There is no file in the request
        insert_user_message_in_db(msg)
    
    # Redirect the user to the main page
    redirect('/')

@app.route('/', methods=['GET'])
def index():
    # Get all the messages from the database
    cur = get_db().cursor()
    cur.execute('SELECT message, photo FROM messages ORDER BY time DESC LIMIT 100')
    msgs = cur.fetchall()
    
    return render_template('index.html', messages=msgs)