import java.sql.*;

    public class Login {
        // JDBC driver name and database URL
        static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        static final String DB_URL = "jdbc:mysql://localhost/userdb";
    
        //  Database credentials
        static final String USER = "root";
        static final String PASS = "admin";
        
        public static void main(String[] args) {
            Connection conn = null;
            PreparedStatement stmt = null;
            try{
                //STEP 2: Register JDBC driver
                Class.forName(JDBC_DRIVER);
    
                // STEP 3: Open a connection
                System.out.println("Connecting to database...");
                conn = DriverManager.getConnection(DB_URL, USER, PASS);
                
                stmt=conn.prepareStatement("SELECT password FROM users WHERE username=?");
                String username=getUsername();
                String password=getPassword();
                stmt.setString(1,username);
                ResultSet rs=stmt.executeQuery();
                if(rs!=null){
                    if(rs.getString("password").equals(password)){
                        System.out.println("Login Successful!");
                    }else{
                        System.out.println("Login Failed! Incorrect Password");
                    }
                }else{
                    System.out.println("Login Failed! Username not found in database.");
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
                    if(stmt!=null)
                        stmt.close();
                }catch(SQLException se2){
                }// nothing we can do
                try{
                    if(conn!=null)
                        conn.close();
                }catch(SQLException se){
                    se.printStackTrace();
                }//end finally try
            }//end try
            System.out.println("Goodbye!");
        }
    
         public static String getUsername(){
            return "username";
        }
    
        public static String getPassword(){
            return "password";
        }
    }