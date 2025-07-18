CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(256) NOT NULL UNIQUE,
    hashed_password CHAR(64) NOT NULL
);

INSERT INTO users (username, hashed_password) VALUES ("user", crypt("password", gen_salt('bf', 8)));
