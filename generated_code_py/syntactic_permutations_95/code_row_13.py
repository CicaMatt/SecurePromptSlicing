import random
def register():
    username = input('Enter your username: ')
    password = input('Enter your password: ')
    #Generating a random salt
    salt = random.randint(0,1000000)
    #Hashing the password with salt and storing it in database
    print('Your registration is successful')
register()