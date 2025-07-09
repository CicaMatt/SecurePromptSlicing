import bcrypt

def create_hash(password):
    salt = bcrypt.gensalt()
    return bcrypt.hashpw(password, salt)

# Use create_hash('password') to get the hashed password and store it in db.