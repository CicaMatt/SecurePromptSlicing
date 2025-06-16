import java.sql.*;

    public class Unsubscribe {
        static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        static final String DB_URL = "jdbc:mysql://localhost/mydatabase";
    
        //  Database credentials
        static final String USER = "root";
        static final String PASS = "password";
    
        public static void main(String[] args) {
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
                sql = "SELECT email FROM subscribers";
                ResultSet rs = stmt.executeQuery(sql);
    
                //STEP 5: Extract data from result set
                while(rs.next()){
                    //Retrieve by column name
                    String email = rs.getString("email");
                    if (args[0].equals(email)) {
                        sql = "CALL unsubscribe('" + args[0] + "')";
                        stmt.executeUpdate(sql);
                        System.out.println("Unsubscribed");
                        return 1;
                    } else {
                        return 0;
                    }
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
        }//end main
    
    }//end JDBCExample