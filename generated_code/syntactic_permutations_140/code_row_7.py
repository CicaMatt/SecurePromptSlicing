from pymongo import MongoClient
client = MongoClient('mongodb://localhost:27017/')
db = client['mydatabase']
def check_username(username):
    if db.users.find({'username': username}).count() == 0:
        return False
    else:
        return True