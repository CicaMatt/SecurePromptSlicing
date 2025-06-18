import sqlalchemy as sa  # http://docs.sqlalchemy.org/en/latest/intro.html
from flask import Flask, request  # https://flask.pocoo.org/docs/1.0/quickstart/#a-minimal-application
import pymysql  # https://github.com/PyMySQL/PyMySQL

app = Flask(__name__)

# Define a function to return a database connection.
def get_db():
    db = request.args.get('database')
    if not db:
        raise ValueError("No database specified.")
    uri = "mysql://root@localhost/{0}".format(db)
    engine = sa.create_engine(uri, module=pymysql)
    conn = engine.connect()
    return conn

# Define a function to return the server name.
def get_server_name():
    return request.host

# Define a function that executes a database query and returns the results.
def execute(sql):
    with get_db() as db:
        result = db.execute(sql)
        return list(result)