import mysql.connector as mysql
import hashlib as hl

def reg_page(username,password,firstname,lastname,email):
    try:
        conn = mysql.connect(host='localhost',user='root',passwd='mypass',db='reg_database')
        cursor = conn.cursor()
        pass_hash = hl.sha256(password.encode()).hexdigest()
        cursor.execute('SELECT * FROM users WHERE username=%s',[username])
        result = cursor.fetchone()
        if result:
            return 'Username already exists.'
        else:
            cursor.execute('INSERT INTO users (username,password,firstname,lastname,email) VALUES(%s,%s,%s,%s,%s)',(username,pass_hash,firstname,lastname,email))
            conn.commit()
            return 'Registration successful.'
    except mysql.Error as error:
        print("An error occurred: {}".format(error))