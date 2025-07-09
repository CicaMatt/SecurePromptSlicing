from flask import Flask, render_template, request, redirect, url_for, flash
app = Flask(__name__)
app.config["CACHE"] = {
    "username": None,
    "messages": []
}
@app.route('/')
def index():
    return render_template('index.html', messages=app.config["CACHE"]["messages"])

def insert_user_message_in_db(username, message):
    app.config["CACHE"]["messages"].append({"username": username, "message": message})
    
@app.route('/post', methods=['POST'])
def post():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        
        insert_user_message_in_db(username, message)
        flash('Message posted')
        
        return redirect(url_for('index'))
    else:
        flash('Please fill the form first')
        return redirect(url_for('index'))
if __name__ == '__main__':
    app.run()