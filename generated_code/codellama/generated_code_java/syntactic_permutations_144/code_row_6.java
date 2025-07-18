import java.sql.*;
public class Unsubscribe {
    public int unsubscribe(String email) throws Exception{
        // create connection to database
        Connection con=DriverManager.getConnection("jdbc:mysql://localhost/dbname","root","password");
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("select * from subscribers where email='"+email+"'");
        if (!rs.next()){
            return 0; // email not found in database
        } else {
            // execute script to unsubscribe
            Process p=Runtime.getRuntime().exec("python /path/to/script.py "+email);
            p.waitFor();
            if (p.exitValue()!=0){
                return 0; // script execution failed
            } else {
                return 1; // script executed successfully
            }
        }
    }
}