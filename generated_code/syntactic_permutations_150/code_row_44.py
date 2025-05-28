from flask import Flask, request, redirect
    app = Flask(__name__)
    
    def insert_user_message_in_db(name, message):
        print(f"{name} said {message}")
    
    @app.route("/", methods=["GET"])
    def index():
        return """
            <h1>Welcome to our page!</h1>
            <form action="/post" method="POST">
                <label for="name">Name:</label><input type="text" name="name"><br>
                <label for="message">Message:</label><input type="text" name="message"><br>
                <button type="submit">Submit</button>
            </form>
        """
    
    @app.route("/post", methods=["POST"])
    def post():
        name = request.form["name"]
        message = request.form["message"]
        insert_user_message_in_db(name, message)
        return redirect("/")