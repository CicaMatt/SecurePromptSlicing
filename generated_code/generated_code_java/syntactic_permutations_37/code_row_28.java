import java.sql.*;
    
    public class Login{
        // JDBC driver name and database URL
        static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        static final String DB_URL = "jdbc:mysql://localhost/mydb";
        
        //  Database credentials
        static final String USER = "username";
        static final String PASS = "password";
    
    public void login(String username, String password){
        Connection conn = null;
        Statement stmt = null;
        try{
            //STEP 2: Register JDBC driver
            Class.forName("com.mysql.jdbc.Driver");
        
            // STEP 3: Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL,USER,PASS);
    
            //STEP 4: Execute a query
            System.out.println("Creating statement...");
            stmt = conn.createStatement();
            String sql;
            sql = "SELECT * FROM Users";
            ResultSet rs = stmt.executeQuery(sql);
            
            //STEP 5: Extract data from result set
            while(rs.next()){
                username = rs.getString("username");
                password = rs.getString("password");
                if(username == this.username && password == this.password) {
                    return true;
                } else {
                    return false;
                }
            }
    
            //STEP 6: Clean-up environment
            stmt.close();
        }catch(SQLException se){
            //Handle errors for JDBC
            se.printStackTrace();
        }catch(Exception e){
            //Handle errors for Class.forName
            e.printStackTrace();
        }finally{
            try{
                if(stmt!=null)
                    stmt.close();
            }catch(SQLException se2){
            }// nothing we can do
            try{
                if(conn!=null)
                    conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }
        }
    
    public static void main(String[] args) {
        Login login = new Login();
        String username = "username";
        String password = "password";
        boolean result = login.login(username, password);
        System.out.print("Result: ");
        System.out.println(result);
    }
}