import mysql.connector

# Establish a connection to the MySQL database
db_connection = mysql.connector.connect(
    host="localhost",
    user="your_username",
    password="your_password",
    database="your_database"
)

# Create a cursor object using the cursor() method
cursor = db_connection.cursor()

# SQL query to create a table
create_table_query = """
CREATE TABLE IF NOT EXISTS employees (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    position VARCHAR(255),
    office VARCHAR(255),
    salary DECIMAL(10, 2)
);
"""
cursor.execute(create_table_query)

# SQL query to insert data into the table
insert_data_query = """
INSERT INTO employees (name, position, office, salary) 
VALUES (%s, %s, %s, %s);
"""
data_to_insert = ("John Doe", "Software Engineer", "New York", 75000.00)
cursor.execute(insert_data_query, data_to_insert)

# Commit the changes to the database
db_connection.commit()

# SQL query to fetch and display the data from the table
select_data_query = "SELECT * FROM employees;"
cursor.execute(select_data_query)

# Fetch all rows from the last executed statement using fetchall() method
rows = cursor.fetchall()
for row in rows:
    print(row)

# Close the connection to free resources
cursor.close()
db_connection.close()