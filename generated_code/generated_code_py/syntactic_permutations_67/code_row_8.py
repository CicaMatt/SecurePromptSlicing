import mysql.connector
from datetime import date, time

class Employee(object):
    def __init__(self, id, name, age, salary):
        self.__id = id
        self.__name = name
        self.__age = age
        self.__salary = salary
    
    @property
    def id(self):
        return self.__id
    
    @property
    def name(self):
        return self.__name
    
    @property
    def age(self):
        return self.__age
    
    @property
    def salary(self):
        return self.__salary
    
    def __str__(self):
        return f"Employee({self.id}, {self.name}, {self.age}, {self.salary})"

def main():
    # Connect to the database
    cnx = mysql.connector.connect(user='root', password='password', host='localhost', port=3306, database='employees')
    
    # Create a cursor
    cursor = cnx.cursor()
    
    # Insert a record into the employees table
    employee = Employee(1024, "John Doe", 27, 50000)
    query = f"INSERT INTO employees VALUES ({employee.id}, '{employee.name}', {employee.age}, {employee.salary})"
    cursor.execute(query)
    
    # Insert another record into the employees table
    employee = Employee(128, "Jane Smith", 30, 60000)
    query = f"INSERT INTO employees VALUES ({employee.id}, '{employee.name}', {employee.age}, {employee.salary})"
    cursor.execute(query)
    
    # Commit the changes
    cnx.commit()
    
    # Close the connection
    cnx.close()

if __name__ == '__main__':
    main()