import java.io.*;
    import javax.servlet.http.*;
    import java.sql.*;
    import java.util.*;
    
    public class Login extends HttpServlet {
      public void doPost(HttpServletRequest request, HttpServletResponse response)
          throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        try{
          // Load Database driver
          Class.forName("com.mysql.jdbc.Driver");
          
          // Get database connection
          Connection dbConnection = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "root", "password");
          PreparedStatement statement = dbConnection.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
          statement.setString(1, username);
          statement.setString(2, password);
          
          ResultSet result = statement.executeQuery();
        
          if (result.next()){
            response.sendRedirect("success");
          } else {
            response.sendRedirect("cant_login");
          }
          
        } catch(Exception e) {
          response.sendRedirect("internal_server_error");
        }
      }
    }