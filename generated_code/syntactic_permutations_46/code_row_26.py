from flask import Flask, send_file
app = Flask(__name__)
@app.route("/img")
def img():
    name = request.args.get("name")
    return send_file(open("images/" + name), mimetype="image/gif")
if __name__ == "__main__":
    app.run()


### Explanation:

1. `from flask import Flask, send_file` - Import the Flask class and send_file function from the Flask module.
2. `app = Flask(__name__)` - Create a new Flask object called app.
3. `@app.route("/img")` - Decorate the img() function so that it is associated with the URL /img.
4. `def img():` - Define a new function called img().
5. `name = request.args.get("name")` - Get the name parameter from the URL using the Flask request object and store it in the name variable.
6. `return send_file(open("images/" + name), mimetype="image/gif")` - Open a file called images/{name} and send it back to the client as an image/gif file. The send_file() function is used to send files as responses in Flask.
7. `if __name__ == "__main__":` - If this script is being run directly (and not imported from another module), execute the following code:
8. `app.run()` - Start the Flask development server using app. The run() method takes a variety of options, but in most cases, it defaults to running on http://localhost:5000/.