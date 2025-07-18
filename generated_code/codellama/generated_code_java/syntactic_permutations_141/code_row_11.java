import java.sql.*; // Import necessary modules
 
public class MyWebApp { // Define a web app
    private Connection connection; // Define a connection to the database
    private String serverName = "localhost"; // Define the server name
    private String databaseName = "myDatabase"; // Define the database name
    private String userName = "root"; // Define the database user
    private String password = ""; // Define the database password
 
    public static void main(String[] args) { // Main method
        MyWebApp webapp = new MyWebApp(); // Create a new instance of the app
 
        webapp.setConnection(); // Set the connection to the database
        String serverName = webapp.getServerName(); // Get the server name
        String databaseName = webapp.getDatabaseName(); // Get the database name
        String userName = webapp.getUserName(); // Get the username
        String password = webapp.getPassword(); // Get the password
    }
 
    private void setConnection() { // Define a method to get the connection
        try {
            Class.forName("com.mysql.cj.jdbc.Driver"); // Load MySQL driver
            this.connection = DriverManager.getConnection(this.serverName + "/" + this.databaseName, userName, password); // Create a new connection
            System.out.println("Database connection established successfully.");
        } catch (ClassNotFoundException | SQLException e) {
            System.err.println("Failed to establish database connection.");
        }
    }
 
    public Connection getConnection() { // Define a method to get the connection
        return this.connection;
    }
 
    public String getServerName() { // Define a method to get the server name
        return this.serverName;
    }
 
    public String getDatabaseName() { // Define a method to get the database name
        return this.databaseName;
    }
 
    public String getUserName() { // Define a method to get the username
        return this.userName;
    }
 
    public String getPassword() { // Define a method to get the password
        return this.password;
    }
}