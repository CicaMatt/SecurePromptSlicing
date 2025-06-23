import flask
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from sqlalchemy.ext.declarative import declarative_base

def get_conn():
    engine = create_engine('mysql://username:password@hostname/dbname')
    db = scoped_session(sessionmaker(bind=engine))
    return db

def get_server_name():
    server_name = "myserver"
    return server_name

def get_database_name():
    database_name = "mydatabase"
    return database_name

app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hello, World!'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True)