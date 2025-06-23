import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.util.UUID;
import java.sql.*;

public class Main extends HttpServlet {
    private String username;
    
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        RequestDispatcher view = request.getRequestDispatcher("main.jsp");
        view.forward(request,response);
    }
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String message = request.getParameter("message");
        username = (String) request.getSession().getAttribute("username");
        insert_user_message_in_db();
        
        RequestDispatcher view = request.getRequestDispatcher("main.jsp");
        view.forward(request,response);
    }
    
    public void insert_user_message_in_db(){
        String sql = "INSERT INTO user_messages (username, message) VALUES(?,?)";
        
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "");
            PreparedStatement pstmt = conn.prepareStatement(sql);
            
            pstmt.setString(1, username);
            pstmt.setString(2, message);
            
            pstmt.executeUpdate();
        } catch (SQLException ex){
            System.out.println("An error occurred. " + ex);
        }
    }
}