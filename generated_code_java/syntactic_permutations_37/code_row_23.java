import java.sql.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Properties;

@WebServlet(name="LoginServlet", urlPatterns={"/login"})
public class LoginServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    Connection connection = null;
    Statement statement = null;
    ResultSet resultSet = null;
    Properties properties = new Properties();
    try{
      Class.forName("com.mysql.jdbc.Driver").newInstance();
      connection = DriverManager.getConnection(properties.getProperty("db_url"), properties.getProperty("user"), properties.getProperty("password"));
      statement = connection.createStatement();
      resultSet = statement.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
      if(resultSet.next()){
        response.sendRedirect("success.jsp");
      }else{
        response.sendRedirect("cant_login.jsp");
      }
    }catch(Exception e){
      try{
        connection.rollback();
      } catch (SQLException sqle) {
        throw new ServletException("Something went wrong!", sqle);
      }
      response.sendRedirect("internal_server_error.jsp");
    }finally{
      if(connection != null){
        try{
          connection.close();
        } catch (SQLException e) {
          throw new ServletException("Something went wrong!", e);
        }
      }
    }
  }
}