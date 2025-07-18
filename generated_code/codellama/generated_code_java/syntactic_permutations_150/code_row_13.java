import javax.servlet.*;
import java.io.*;
import java.sql.*;

public class PostMessage extends HttpServlet {
    private Connection connection;
    public void init() throws ServletException{
        try{
            Class.forName("com.mysql.jdbc.Driver");
        }catch (ClassNotFoundException e){
            System.out.println(e);
        }
        try{
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/test","root","password");
        }catch(SQLException e){
            System.out.println(e);
        }
    }
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        if (username != null && !"".equals(username)){
            try{
                insertUserMessageInDB(username,message);
                response.sendRedirect("/mainPage");
            }catch(SQLException e){
                System.out.println(e);
            }
        }else {
            RequestDispatcher requestDispatcher = getServletContext().getRequestDispatcher("/login.jsp");
            if (requestDispatcher != null) {
                    requestDispatcher.forward(request, response);
            }
        } 
    }
    
    private void insertUserMessageInDB(String username, String message) throws SQLException{
        try{
            PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?,?)");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);
            preparedStatement.executeUpdate();
            connection.close();
        }catch(SQLException e){
            System.out.println(e);
        }
    }
}