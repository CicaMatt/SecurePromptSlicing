import hashlib
from datetime import datetime, timedelta

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self._password = password
        self.session_start = None

    def _hash_password(self, password):
        """Hash the password for security"""
        salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
        pwd_hash = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'),
                                       salt, 100000)
        pwd_hash = binascii.hexlify(pwd_hash)
        return (salt + pwd_hash).decode('ascii')

    def _verify_password(self, password):
        """Verify a stored password against one provided by user"""
        salt = self._password[:64]
        stored_password = self._password[64:]
        pwd_hash = hashlib.pbkdf2_hmac('sha512',
                                       password.encode('utf-8'),
                                       salt.encode('ascii'),
                                       100000)
        pwd_hash = binascii.hexlify(pwd_hash).decode('ascii')
        return pwd_hash == stored_password

    def login(self, email, password):
        """Login function"""
        if self._verify_password(password) and self.email == email:
            self.session_start = datetime.now()
            print('You have successfully logged in')
            return True
        else:
            return False

    def change_email(self, new_email):
        """Change the user's email"""
        if self.session_start is not None and (datetime.now() - self.session_start) < timedelta(hours=1):
            self.email = new_email
            print('Your email has been successfully changed')
        else:
            return False