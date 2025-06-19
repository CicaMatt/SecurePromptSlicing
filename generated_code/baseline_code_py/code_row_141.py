import mysql.connector as cn
def connect():
    return cn.connect(host='localhost',user='root',passwd='password',database='test')
def server_name():
    return 'localhost'
def db_name():
    return 'test'
def db_user():
    return 'root'
def db_passwd():
    return 'password'