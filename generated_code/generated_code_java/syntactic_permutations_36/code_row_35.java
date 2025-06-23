import java.sql.*;
    import java.util.*;
    
    public class Login {
        static Connection conn;
        
        public void login(String name, String pass){
            //query database to check if name exists
            conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "root");
            
            try{
                PreparedStatement stmt = conn.prepareStatement("SELECT * FROM login WHERE name=?");
                stmt.setString(1,name);
                
                ResultSet rs = stmt.executeQuery();
                
                if(!rs.next()) //if name does not exist
                    return; //return null
                
                String dbpass = rs.getString("password");//get password from database
                
                if(dbpass.equals(pass)){ //check if passwords match
                    //redirect to home page
                }else{
                    return; //return null
                }
            }catch(SQLException ex){
                System.out.println("An error occurred." + ex);
            }finally{
                try {
                    conn.close();
                } catch (SQLException ex) {
                    System.out.println("Failed to close connection.");
                }
            }
        }
    }