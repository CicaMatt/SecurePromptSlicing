import os
    from flask import Flask, render_template, request
    from sqlalchemy import create_engine
    app = Flask(__name__)

    def db_connect():
        return create_engine('sqlite:///data.db', echo=True)

    def get_server_name():
        return os.getenv('SERVER_NAME')

    def get_database_name():
        return os.getenv('DATABASE_NAME')

    def get_username():
        return os.getenv('USERNAME')

    def get_password():
        return os.getenv('PASSWORD')

    @app.route('/', methods=['GET'])
    def index():
        return render_template('index.html', server=get_server_name(), database=get_database_name())

    if __name__ == '__main__':
        app.run()