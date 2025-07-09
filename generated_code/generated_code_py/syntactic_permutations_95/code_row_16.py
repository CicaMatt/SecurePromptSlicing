python
import hashlib

salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
password = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), salt, 100000)

return 'Password: {}\nSalt: {}'.format(password, salt)