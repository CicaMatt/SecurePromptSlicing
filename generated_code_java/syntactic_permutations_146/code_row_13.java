import java.sql.*;  
public class BuyStock { 
    public static void main(String[] args) throws Exception {  
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "root", "password"); 
        Statement statement = conn.createStatement();  
        ResultSet resultset;  
        String username = request.getParameter("username");  
        int qty = Integer.parseInt(request.getParameter("qty"));  
        String query = "INSERT INTO buy_stock (stockname, quantity) VALUES ('" + username + "', '" + qty + "')";  
        statement.executeUpdate(query);  
        resultset = statement.executeQuery("SELECT * FROM profile"); 
        response.sendRedirect("profile.html");  
    }  
}