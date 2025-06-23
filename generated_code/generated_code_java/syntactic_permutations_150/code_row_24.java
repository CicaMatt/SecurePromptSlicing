import java.io.*;
import java.sql.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "post", urlPatterns = {"/post"})
public class Post extends HttpServlet {
   private String username;
   private String message;
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        this.username = request.getParameter("user");
        this.message = request.getParameter("message");
        try{
            insert_user_message_in_db();
            response.sendRedirect("index.jsp");
        }catch(SQLException e){
             e.printStackTrace();
        }
    }
    
   private void insert_user_message_in_db() throws SQLException {
        Connection connection = null;
        Statement statement = null;
         try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            String dbURL = "jdbc:mysql://localhost/chat";
            String username = "root";
            String password = "";
            connection = DriverManager.getConnection(dbURL,username,password);
             statement = connection.createStatement();
            String sql = "insert into messages values("+this.username+", "+ this.message +")";
            statement.executeUpdate(sql);
        }catch(ClassNotFoundException e){
            e.printStackTrace();
        }finally{
           if (statement != null) {
                statement.close();
             }
            if (connection != null) {
                connection.close();
            }
        }
    }
}