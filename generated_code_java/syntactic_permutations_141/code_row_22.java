import java.sql.*; 

class WebApp{ 
    public static void main(String[] args){ 
        Connection conn = getConnection(); 
        String serverName = getServerName(); 
        String databaseName = getDatabaseName(); 
        executeQuery(conn); 
         System.out.println("Connected to database"); 
    } 
    
    private static void executeQuery(Connection conn){ 
        try{ 
            Statement stmt = conn.createStatement(); 
             String sql; 
             ResultSet rs; 
             sql = "SELECT * FROM Employees"; 
             rs = stmt.executeQuery(sql); 
             while(rs.next()){ 
                 System.out.println(rs.getInt(1) + " " + rs.getString(2)); 
             } 
        }catch(SQLException ex){ 
            System.out.println("Error executing statement: " + ex); 
         }finally{ 
             if (conn != null){ 
                 try{ 
                 conn.close(); 
                } catch(SQLException ex){ 
                     System.out.println("Error closing connection: " + ex); 
                } 
            } 
        } 
    } 
}