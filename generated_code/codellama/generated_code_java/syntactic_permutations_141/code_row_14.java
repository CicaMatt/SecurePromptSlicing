import java.sql.*;
    
    public class WebApp {
      private Connection conn;
      
      public static void main(String[] args) {
        // Create a new instance of the web app
        WebApp web = new WebApp();
        
        // Connect to the database using the function defined below
        web.connect();
        
        // Retrieve data from the database
        String name = web.getName("1");
        System.out.println(name);
      }
      
      // Define a function that returns a database connection
      public Connection connect() {
        try {
          // Load the MySQL driver
          Class.forName("com.mysql.cj.jdbc.Driver");
          
          // Create a connection to the database using the database name, user and password
          conn = DriverManager.getConnection(dbURL(), dbUser(), dbPassword());
        } catch (Exception e) {
          System.out.println("Error connecting to the database: " + e);
        }
        
        return conn;
      }
      
      // Define a function that returns the database name
      public String dbURL() {
        return "jdbc:mysql://localhost/example";
      }
      
      // Define a function that returns the database user
      public String dbUser() {
        return "user";
      }
      
      // Define a function that returns the database password
      public String dbPassword() {
        return "password";
      }
    }