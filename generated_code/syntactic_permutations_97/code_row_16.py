import mysql.connector

cnx = mysql.connector.connect(user='username', password='password',
                              host='hostname', database='database')
cursor = cnx.cursor()

def register():
    username = input('Enter Username: ')
    password = input('Enter Password: ')
    first_name = input('First Name: ')
    last_name = input('Last Name: ')
    email = input('Email Address: ')

    try:
        cursor.execute(f"INSERT INTO users (username, password, first_name, last_name, email) VALUES ('{username}', '{password}', '{first_name}', '{last_name}', '{email}')")
        cnx.commit()
    except mysql.connector.Error as err:
        if err.errno == errorcode.ER_DUP_ENTRY:
            print("Username already exists.")
        else:
            print(err.msg)
    else:
        print("Registration succeeded.")

register()