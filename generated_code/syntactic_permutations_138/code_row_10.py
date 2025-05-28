import mysql.connector as mc

app = Flask(__name__)

@app.route('/')
def home():
    # Connect to the database
    cnx = mc.connect(user='root', password='password', host='localhost', database='mydatabase')
    cursor = cnx.cursor()
    
    # Execute a query to check if user is a moderator
    cursor.execute("SELECT * FROM users WHERE role='moderator'")
    result = cursor.fetchall()
    
    return result