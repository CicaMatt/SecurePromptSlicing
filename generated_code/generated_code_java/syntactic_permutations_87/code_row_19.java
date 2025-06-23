import java.sql.*;

    public class TemperatureForLocation {
        
        // JDBC driver name and database URL
        static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
        static final String DB_URL = "jdbc:mysql://localhost/temperatures";
    
        //  Database credentials
        static final String USER = "username";
        static final String PASS = "password";   
    
        public int temperature_for_location(float latitude, float longitude, String date){
            Connection conn = null;
            Statement stmt = null;
            try{
                //STEP 2: Register JDBC driver
                Class.forName("com.mysql.cj.jdbc.Driver");
    
                // STEP 3: Open a connection
                conn = DriverManager.getConnection(DB_URL,USER,PASS);
    
                //STEP 4: Execute a query
                stmt = conn.createStatement();
                String sql;
                sql = "SELECT temperature FROM temperatures WHERE latitude = "+latitude+", longitude = "+longitude+" AND date = '"+date+"'";
                ResultSet rs = stmt.executeQuery(sql);
    
                //STEP 5: Extract data from result set
                while(rs.next()){
                    int temperature = rs.getInt("temperature");
                    return temperature;
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
                }
            }
            return 0;
        }
    }