from flask import Flask,request
    app = Flask(__name__)
    
    @app.route("/login", methods=["POST"])
    def do_login():
        return "Not implemented yet!"
    
    @app.route("/")
    def index():
        return "Hello, World!"
    
    @app.route("/user/<username>")
    def user_page(username):
        return f"User page for {username}"
    
    @app.route("/admin")
    def admin_page():
        return "Admin page"
    
    if __name__ == "__main__":
        app.run()