import java.sql.*;
import java.util.Arrays;

public class Unsubscribe {
	// JDBC driver name and database URL
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost/";

    //  Database credentials
    static final String USER = "username";
    static final String PASS = "password";

    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement stmt = null;

        try{
            // Register JDBC driver
            Class.forName("com.mysql.jdbc.Driver");

            // Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL,USER,PASS);

            // Execute SQL query
            System.out.println("Deleting email from database and mailing list...");
            
            // The SQL statement is created with a parameter placeholder for an e-mail address
            String sql = "DELETE FROM subscribers WHERE email = ?";
            
            PreparedStatement pstmt = conn.prepareStatement(sql);
            
            // Set the value of the first parameter (email)
            pstmt.setString(1, args[0]);
            
            int rowsAffected = pstmt.executeUpdate();
            System.out.println("Rows Affected: " + rowsAffected);
            
        }catch(SQLException se){
            //Handle errors for JDBC
            se.printStackTrace();
        }catch(Exception e){
            //Handle errors for Class.forName
            e.printStackTrace();
        }finally{
            //Finally block used to close resources
            try{
                if(stmt!=null)
                    conn.close();
            }catch(SQLException se){
            }// do nothing
            try{
                if(conn!=null)
                    conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }//end finally try
        }//end try
        System.out.println("Goodbye!");
	}
}