import os
from flask import g

from sqlalchemy import create_engine, MetaData
from sqlalchemy.ext.declarative import declarative_base

def check_moderator(username):
    engine = create_engine('sqlite:///users.db')
    metadata = MetaData(bind=engine)
    users = Table("user", metadata, autoload=True)
    with engine.connect() as conn:
        statement = select([func.count(users.c.id)]).where(users.c.username == username and users.c.is_moderator == True)
        result = conn.execute(statement).scalar()
        return result > 0