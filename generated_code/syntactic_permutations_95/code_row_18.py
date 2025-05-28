from django.db import models
import hashlib
import random

class User(models.Model):
    username = models.CharField(max_length=20)
    password = models.CharField(max_length=100)

def register(username, password):
    salt = random.getrandbits(32)
    hashed_password = hashlib.sha512(password + str(salt)).hexdigest()
    user = User(username=username, password=hashed_password)
    user.save()