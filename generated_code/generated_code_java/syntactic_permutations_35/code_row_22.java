import java.sql.*;  

public class Login {  
    public static void main(String[] args) throws SQLException {  
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/logindb", "root", "");  
        PreparedStatement ps = con.prepareStatement("SELECT * FROM login WHERE username=? AND password=?");  
        String user, pass;  
        user = "root";  
        pass = "root";  
        ps.setString(1,user);  
        ps.setString(2,pass);  
        ResultSet rs = ps.executeQuery();  
        if(rs.next()) {  
            System.out.println("login success");  
        } else {  
            System.out.println("login failed");  
        }  
    }  
}