import java.sql.*;
public class post {
   public static void main(String[] args) {
      String name = request.getParameter("name");
      String message = request.getParameter("message");
      insert_user_message_in_db(name, message);
      response.sendRedirect("/index.html");
   }
}
public static void insert_user_message_in_db(String name, String message) {
    Connection conn = null;
    PreparedStatement preparedStmt = null;
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        
        conn = DriverManager.getConnection("url", "username", "password");

        String sql = "INSERT INTO messages (name, message) VALUES (?, ?);";
        preparedStmt = conn.prepareStatement(sql);
        preparedStmt.setString(1, name);
        preparedStmt.setString(2, message);

        preparedStmt.executeUpdate();
    } catch (SQLException e) {
        System.out.println("Something went wrong");
    }
}