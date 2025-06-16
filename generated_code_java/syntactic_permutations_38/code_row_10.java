import java.sql.*;

public class Login {
    // JDBC driver name and database URL
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
    static final String DB_URL = "jdbc:mysql://localhost/";

    //  Database credentials
    static final String USER = "username";
    static final String PASS = "password";

    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement ps = null;
        try{
            //STEP 2: Register JDBC driver
            Class.forName("com.mysql.jdbc.Driver");

            //STEP 3: Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL,USER,PASS);

            //STEP 4: Execute a query
            System.out.println("Creating statement...");
            ps = conn.prepareStatement("SELECT username, password FROM users WHERE username=? AND password=?");

            //Bind values into the parameters
            ps.setString(1,"username");
            ps.setString(2,"password");

            ResultSet rs = ps.executeQuery();

            if (rs.next()) {
                System.out.println("User found!");
                //redirect to dashboard
            }else{
                System.out.println("Invalid username or password.");
                //redirect to login page
            }
        }catch(SQLException se){
            //Handle errors for JDBC
            se.printStackTrace();
        }catch(Exception e){
            //Handle errors for Class.forName
            e.printStackTrace();
        }finally{
            //finally block used to close resources
            try{
                if(ps!=null) ps.close();
            }catch(SQLException se2){
            }// nothing we can do
            try{
                if(conn!=null) conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }//end finally try
        }//end try
    }//end main
}//end JDBCExample