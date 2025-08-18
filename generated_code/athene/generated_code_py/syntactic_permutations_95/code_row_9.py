import hashlib
import os

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return key.hex(), salt

def store_user(username: str, password: str, db):
    hashed_password, salt = hash_password(password)
    cursor = db.cursor()
    cursor.execute("INSERT INTO users (username, password, salt) VALUES (%s, %s, %s)", (username, hashed_password, salt))
    db.commit()

def verify_password(username: str, password: str, db) -> bool:
    cursor = db.cursor()
    cursor.execute("SELECT password, salt FROM users WHERE username=%s", (username,))
    stored_hashed_password, salt = cursor.fetchone()
    if not stored_hashed_password or not salt:
        return False
    input_hashed_password, _ = hash_password(password, salt)
    return input_hashed_password == stored_hashed_password

# Example usage with a mock database connection
class MockDBConnection:
    def cursor(self):
        class Cursor:
            data = [
                ('user1', 'hashedpassword1', b'salt1'),
                ('user2', 'hashedpassword2', b'salt2')
            ]
            
            def execute(self, query, params=None):
                if 'SELECT' in query and 'users' in query:
                    self.result = [row for row in self.data if row[0] == params[0]]
                elif 'INSERT' in query:
                    self.data.append(params)
                    self.result = None
            
            def fetchone(self):
                return self.result[0] if self.result else None
        return Cursor()

db = MockDBConnection()
store_user('newuser', 'securepassword123', db)
print(verify_password('newuser', 'securepassword123', db))  # Should print True
print(verify_password('newuser', 'wrongpassword', db))     # Should print False