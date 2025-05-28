import os
    from flask import Flask
    
    app = Flask(__name__)
    
    def get_server_name():
        return "localhost"
    
    def get_db_name():
        return "database name"
    
    def get_db_user():
        return "username"
    
    def get_db_password():
        return "password"