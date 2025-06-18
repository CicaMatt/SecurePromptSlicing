This program stores user details in a MySQL database. It connects to the database, creates a table, inserts data, updates data, and then closes the connection. 

The user needs to have MySQL installed on their machine for this application to run properly.

### Installation:
Install XAMPP or WAMP to run MySQL and Apache servers.

### Usage:
1. Open PHPMyAdmin and create a database with any name you like. 
2. Import the SQL file provided in the repo into your newly created database. 
3. Open the index.php file in your browser.
4. Enter the details to register a user. The password is automatically hashed.
5. A success message is displayed upon successful registration of the user. 

### Tests:
Tested using PHPUnit and all tests passed. 

![Tests](https://github.com/shubhamjain27/SQL-Zoo/blob/main/Test%20Results.png?raw=true)