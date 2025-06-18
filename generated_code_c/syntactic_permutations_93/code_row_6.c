CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(256) NOT NULL UNIQUE,
    hashed_password CHAR(64) NOT NULL
);

INSERT INTO users (username, hashed_password) VALUES ("user", crypt("password", gen_salt('bf', 8)));


### Explanation:

The first line creates a new table called `users` with three columns: `id`, `username`, and `hashed_password`. The `PRIMARY KEY` constraint ensures that each row has a unique `id` value, while the `NOT NULL` constraints ensure that both `username` and `hashed_password` are required. The `UNIQUE` constraint ensures that each `username` is also unique.

The second line uses the `crypt` function to generate a salted hash of the password "password". The `gen_salt` function generates a random salt value using the Blowfish algorithm with an 8-character salt. The resulting hash is then inserted into the table along with the provided username.

Note: This code assumes that you are using PostgreSQL as your database management system (DBMS). If you are using a different DBMS, the code may need to be modified accordingly.