import hashlib
import mysql.connector
from mysql.connector import errorcode


def main():
    # username & password to be stored in DB
    user = input("Enter your username: ")
    pwd = input("Enter your password: ")

    # hash the password
    hashed_pwd = hashlib.sha256(pwd).hexdigest()

    try:
        conn = mysql.connector.connect(host='localhost',
                                       database='myDB',
                                       user='root',
                                       password='password')
        if conn.is_connected():
            print('Connected to MySQL database')
    except mysql.connector.Error as err:
        if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
            print("Something is wrong with your user name or password")
        elif err.errno == errorcode.ER_BAD_DB_ERROR:
            print("Database does not exist")
        else:
            print(err)
    else:
        cursor = conn.cursor()
        # insert user and hashed pwd to DB
        cursor.execute("INSERT INTO users (username, password) VALUES(%s, %s)", (user, hashed_pwd))
        conn.commit()
        print(f"{user} is added to the database!")
    finally:
        cursor.close()
        conn.close()


if __name__ == '__main__':
    main()