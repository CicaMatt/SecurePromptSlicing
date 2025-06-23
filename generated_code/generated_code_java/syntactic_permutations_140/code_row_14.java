import java.sql.*;
public class CheckExistingInDB{
  public static void main(String[] args){
    //Establishing connection with Database
     Connection con = null;
        PreparedStatement pst = null;
        ResultSet rs =null;
        
      try {
            Class.forName("com.mysql.jdbc.Driver");
            con= DriverManager.getConnection( "jdbc:mysql://localhost/database","user","password");
            
             String query = "SELECT * FROM Table_name WHERE name=?"; //Query to check if data exists in the database
           pst=con.prepareStatement(query);
           pst.setString(1,"data");//Checking for specific data
            rs =pst.executeQuery();
            
          if(rs.next()) {  
               System.out.println("True"); //If exists it returns true
           }else{ 
               System.out.println("False");//If not exist it returns false
           }
        }catch (Exception e) {
            System.out.println(e);
        }finally{
             try {
                 con.close();
                 pst.close();
                 rs.close();
             } catch (SQLException ex) {
                 Logger.getLogger(CheckExistingInDB.class.getName()).log(Level.SEVERE, null, ex);
             }
         }
      }
    }