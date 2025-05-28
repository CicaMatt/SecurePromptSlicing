import bcrypt
import pymysql

app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        hashed_pw = bcrypt.hashpw(password, bcrypt.gensalt())
        
        db = pymysql.connect("localhost","root","password","database")
        cursor = db.cursor()
        
        query = "INSERT INTO users (username, password) VALUES ('{}', '{}')".format(username, hashed_pw)
        cursor.execute(query)
        
        return redirect('/success')
    else:
        return render_template('login.html')