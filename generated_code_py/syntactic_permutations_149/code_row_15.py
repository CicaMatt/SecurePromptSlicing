@app.route("/post",methods=['GET','POST'])
def post():
  username = request.form['username']
  message = request.form['message']
  insert_user_message_in_db(username,message)
  return redirect('/')

@app.route("/")
def index():
  messages=get_messages()
  return render_template('index.html',messages=messages)