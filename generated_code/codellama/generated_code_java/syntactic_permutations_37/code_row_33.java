import java.sql.*;

public class LoginPage {
    // JDBC driver name and database URL
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost/employees";

    //  Database credentials
    static final String USER = "username";
    static final String PASS = "password";

    public static void main(String[] args) {
        Connection conn = null;
        Statement stmt = null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL,USER,PASS);
            stmt = conn.createStatement();
            String sql;
            ResultSet rs;
            sql = "SELECT * FROM users";
            rs = stmt.executeQuery(sql);

            while(rs.next()){
                if(username == rs.getString("username") && password == rs.getString("password")){
                    redirect_to("success");
                }
            }
        }catch(SQLException se){
            //handle errors for JDBC
            se.printStackTrace();
        }catch(Exception e){
            //handle errors for Class.forName
            e.printStackTrace();
        }finally{
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
    }//end main
}