import java.sql.*;
public class Unsubscribe {
  private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
  private static final String DB_URL = "jdbc:mysql://localhost/test";

  //  Database credentials
  private static final String USER = "root";
  private static final String PASS = "";

  public Unsubscribe(String email) {
    Connection conn = null;
    Statement stmt = null;
    try {
      // STEP 2: Register JDBC driver
      Class.forName("com.mysql.jdbc.Driver");

      // STEP 3: Open a connection
      System.out.println("Connecting to database...");
      conn = DriverManager.getConnection(DB_URL, USER, PASS);

      // STEP 4: Execute a query
      System.out.println("Creating statement...");
      stmt = conn.createStatement();
      String sql;
      sql = "SELECT email FROM users WHERE email = " + email;
      ResultSet rs = stmt.executeQuery(sql);

      // STEP 5: Extract data from result set
      while (rs.next()) {
        // Retrieve by column name
        String email = rs.getString("email");
        if (email != null) {
          sql = "DELETE FROM users WHERE email = " + email;
          stmt = conn.createStatement();
          rs = stmt.executeQuery(sql);
          // Unsubscribe the user from the mailing list
          // ...
          System.out.println("User is unsubscribed.");
        } else {
          System.out.println("The user is already unsubscribed.");
        }
      }
    } catch (SQLException se) {
      // Handle errors for JDBC
      se.printStackTrace();
    } catch (Exception e) {
      // Handle errors for Class.forName
      e.printStackTrace();
    } finally {
      // finally block used to close resources
      try {
        if (stmt != null)
          conn.close();
      } catch (SQLException se) {
      } // do nothing
      try {
        if (conn != null)
          conn.close();
      } catch (SQLException se) {
        se.printStackTrace();
      } // end finally try
    } // End try
  }
}