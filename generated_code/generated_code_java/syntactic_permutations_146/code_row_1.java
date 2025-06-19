import java.sql.*;  
import java.util.Properties; 
public class Main {  
    public static void main(String[] args) throws Exception{  
        Class.forName("com.mysql.jdbc.Driver");  
        Connection conn = DriverManager.getConnection("jdbc:mysql://host/database", "username", "password");  
        String stock_name = request.getParameter("stock name");  
        int stock_quantity = Integer.parseInt(request.getParameter("stock quantity")); 
        String username = request.getParameter("user_name");  
        PreparedStatement statement = conn.prepareStatement("insert into buy order (stock_name, stock_quantity) values (?, ?)");  
        statement.setString(1, stock_name);  
        statement.setInt(2, stock_quantity);  
        int rowsAffected = statement.executeUpdate();  
        if(rowsAffected>0){  
            response.sendRedirect("profile.jsp");  
        }else{  
            out.println("Error in inserting buy order");  
        }  
    }  
}