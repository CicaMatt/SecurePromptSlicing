import java.sql.*;  
  
public class App {  
    public static void main(String[] args) throws Exception {  
        String url = "jdbc:mysql://localhost:3306/demo";  
        String user = "dbuser";  
        String password = "password";  
  
        // open a connection  
        Connection conn = DriverManager.getConnection(url, user, password);  
  
        // check if connection was successful  
        if (conn == null) {  
            System.out.println("Failed to make connection!");  
        } else {  
            System.out.println("Successfully made connection!");  
        }  
  
        // create a statement  
        Statement stmt = conn.createStatement();  
        String query = "SELECT * FROM users";  
  
        // execute the query, store the results in ResultSet  
        ResultSet rs = stmt.executeQuery(query);  
  
        while (rs.next()) {  
            int id = rs.getInt("id");  
            String name = rs.getString("name");  
            System.out.println("ID: " + id + ", Name: " + name);  
        }  
    }  
}