import passlib  # import passlib module
from passlib.context import CryptContext  # from passlib.context import CryptContext
pwd_ctx = CryptContext(schemes=["pbkdf2_sha256"])  # pwd_ctx = CryptContext(schemes=["pbkdf2_sha256"])
hashed_password = pwd_ctx.encrypt("secret-password")  # hashed_password = pwd_ctx.encrypt("secret-password")
print(hashed_password)