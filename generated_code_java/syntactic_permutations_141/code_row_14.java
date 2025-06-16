import mysql.connector
from flask import Flask, request, g
from config import Config


app = Flask(__name__)
app.config.from_object(Config)

def get_db():
    if 'db' not in g:
        g.db = mysql.connector.connect(host=app.config['DATABASE_HOST'],
                                         user=app.config['DATABASE_USER'],
                                         password=app.config['DATABASE_PASSWORD'],
                                         database=app.config['DATABASE'])
        
    return g.db

def close_db(e=None):
    db = g.pop('db', None)
    if db is not None:
        db.close()

def get_name():
    return "TechCode"

def get_database():
    return app.config['DATABASE']

def get_username():
    return app.config['DATABASE_USER']

def get_password():
    return app.config['DATABASE_PASSWORD']


### Response:

import mysql.connector;
from flask import Flask, request, g;
from config import Config;

app = Flask(__name__);
app.config.from_object(Config);

def get_db():
    if 'db' not in g:
        g.db = mysql.connector.connect(host=app.config['DATABASE_HOST'],
                                         user=app.config['DATABASE_USER'],
                                         password=app.config['DATABASE_PASSWORD'],
                                         database=app.config['DATABASE']);
        return g.db;
    
def close_db(e=None):
    db = g.pop('db', None);
    if db is not None:
        db.close();

def get_name():
    return "TechCode";

def get_database():
    return app.config['DATABASE'];

def get_username():
    return app.config['DATABASE_USER'];

def get_password():
    return app.config['DATABASE_PASSWORD'];

### Response:

import mysql.connector
from flask import Flask, request, g
from config import Config

app = Flask(__name__)
app.config.from_object(Config)

def get_db():
    if 'db' not in g:
        g.db = mysql.connector.connect(host=app.config['DATABASE_HOST'],
                                         user=app.config['DATABASE_USER'],
                                         password=app.config['DATABASE_PASSWORD'],
                                         database=app.config['DATABASE'])
        return g.db

def close_db(e=None):
    db = g.pop('db', None)
    if db is not None:
        db.close()

def get_name():
    return "TechCode"

def get_database():
    return app.config['DATABASE']

def get_username():
    return app.config['DATABASE_USER']

def get_password():
    return app.config['DATABASE_PASSWORD']