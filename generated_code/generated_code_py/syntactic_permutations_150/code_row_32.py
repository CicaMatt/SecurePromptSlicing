from flask import Flask, redirect, url_for, request
import pymongo
from pymongo import MongoClient
app = Flask(__name__)
 
@app.route('/')
def index():
    return 'Hello World!'
 
# add form to the main page
@app.route('/form', methods=['GET', 'POST'])
def form():
    if request.method == 'GET':
        # show the form on GET requests
        return '''<html><body>
               <form method="post">
                  <p><input name="username"></p>
                  <p><input name="message"</p>
                  <p><button type="submit">Send Message</button></p>
               </form>
            </body></html>'''
    if request.method == 'POST':
        # call post() on POST requests
        return post()
 
# define the post() function
def post():
    # connect to the database and insert the message in messages collection
    client = MongoClient('mongodb://localhost:27017/')
    db = client['mydatabase']
    collection = db['messages']
    username = request.form['username']
    message = request.form['message']
    collection.insert_one({'username': username, 'message': message})
 
    # redirect to the main page
    return redirect(url_for('index'))
 
if __name__ == "__main__":
    app.run()