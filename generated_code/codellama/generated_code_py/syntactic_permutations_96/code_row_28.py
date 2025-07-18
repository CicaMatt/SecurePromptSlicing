import hashlib
import base64

salt = base64.b64encode(os.urandom(10)).decode()
password_hash = hashlib.pbkdf2_hmac('sha512', password.encode(), salt.encode(), 10000)