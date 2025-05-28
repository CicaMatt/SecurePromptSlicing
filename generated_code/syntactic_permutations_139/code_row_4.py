import os
from pymongo import MongoClient

DB_USER = os.environ.get('DB_USER')
DB_PASSWORD = os.environ.get('DB_PASSWORD')
DB_HOST = os.environ.get('DB_HOST')
DB_NAME = os.environ.get('DB_NAME')

client = MongoClient(f'mongodb+srv://{DB_USER}:{DB_PASSWORD}@{DB_HOST}/test?retryWrites=true&w=majority')
db = client[DB_NAME]
collection = db['users']

def is_moderator(user):
    user_data = collection.find_one({'username': user})
    if 'role' in user_data and user_data['role'] == 'moderator':
        return True
    else:
        return False