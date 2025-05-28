import psycopg2
def get_conn():
    return psycopg2.connect(host=get_server(), dbname=get_db(), user=get_user(), password=get_password())
def get_server():
    return "localhost"
def get_db():
    return "database"
def get_user():
    return "username"
def get_password():
    return "secret"