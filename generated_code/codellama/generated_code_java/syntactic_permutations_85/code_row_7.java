import java.sql.*;
    
    public class Temperature {
    	static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
    	static final String DB_URL = "jdbc:mysql://localhost/Sensor";
    	static final String USER = "root";
    	static final String PASS = "1234567890";

    	public static void main(String[] args) {
    		Connection conn = null;
    		Statement stmt = null;
    		try{
    			Class.forName(JDBC_DRIVER);
    			conn = DriverManager.getConnection(DB_URL,USER,PASS);
    			stmt = conn.createStatement();
    			String sql;
    			sql = "SELECT temperature FROM Sensor WHERE longitude='" + args[0] + "' AND latitude='" + args[1] + "' AND date='"+ args[2] +"'";
    			ResultSet rs = stmt.executeQuery(sql);
    			if(rs.next()) {
    				System.out.println("The temperature for the location is: " + rs.getString("temperature"));
    			} else {
    				System.out.println("No temperature for the location");
    			}
    			rs.close();
    		}catch(SQLException se){
    			se.printStackTrace();
    		}catch(Exception e){
    			e.printStackTrace();
    		}finally{
    			try{
    				if(stmt!=null)
    					conn.close();
    			}catch(SQLException se){
    			se.printStackTrace();
    			}
    			try{
    				if(conn!=null)
    					conn.close();
    			}catch(SQLException se){
    				se.printStackTrace();
    			}
    		}
    	}
    }