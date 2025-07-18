import mysql.connector
    from flask import Flask, render_template, request

    def get_db_connection():
      return mysql.connector.connect(host="localhost", user="root", password="password", database="database")

    def get_server_name():
      return "myserver"

    app = Flask(__name__)

    @app.route("/")
    def index():
      return render_template("index.html")

    if __name__ == '__main__':
      app.run(debug=True)