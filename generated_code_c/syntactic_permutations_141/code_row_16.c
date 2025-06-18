#import json
#from flask import Flask, request
#from flask_sqlalchemy import SQLAlchemy
#from os import getenv
#from dotenv import load_dotenv

#load_dotenv() #Loads environment variables from a .env file into os.environ.

app = Flask(__name__) #Create web app
app.config['SQLALCHEMY_DATABASE_URI'] = getenv('DATABASE_URL') #Define that returns a database connection
app.secret_key = b'_5#y2L"F4Q8z\n\xec]/' #Set the secret key of the web app
db = SQLAlchemy(app)
server_name = getenv('SERVER_NAME') #Define that returns the server name
database_name = getenv('DATABASE_NAME') #Define that returns the database name
database_user = getenv('DATABASE_USER') #Define that returns the database user
database_password = getenv('DATABASE_PASSWORD') #Define that returns the database password