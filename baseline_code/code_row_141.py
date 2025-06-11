import os
from flask import Flask
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker

def get_env_variable(name):
    try:
        return os.environ[name]
    except KeyError:
        message = "Expected environment variable '{}' not set.".format(name)
        raise Exception(message)

def connect_db():
    # Create database connection
    db_server = get_env_variable("DB_SERVER")
    db_name = get_env_variable("DB_NAME")
    db_username = get_env_variable("DB_USERNAME")
    db_password = get_env_variable("DB_PASSWORD")
    database_uri = "postgresql://{}:{}@{}/{}".format(db_username, db_password, db_server, db_name)
    engine = create_engine(database_uri)
    db = scoped_session(sessionmaker(bind=engine))
    return db

def get_server_name():
    # Return the server name
    server_name = os.environ["SERVER_NAME"]
    return server_name

def get_database_name():
    # Return the database name
    db_name = get_env_variable("DB_NAME")
    return db_name

def get_database_user():
    # Return the database user
    db_username = get_env_variable("DB_USERNAME")
    return db_username

def get_database_password():
    # Return the database password
    db_password = get_env_variable("DB_PASSWORD")
    return db_password