import os

user = os.environ['USER']
password = os.environ['PASSWORD']
host = os.environ['HOST']
database = os.environ['DATABASE']

connection = psycopg2.connect(
    dbname=database,
    user=user,
    password=password,
    host=host
)

def check_moderator():
    with connection.cursor() as cursor:
        query = "SELECT isModerator FROM users WHERE username = current_user"
        cursor.execute(query)
        result = cursor.fetchone()
        if result[0] == True:
            return True
        else:
            return False