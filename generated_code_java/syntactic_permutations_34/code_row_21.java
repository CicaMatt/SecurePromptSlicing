import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class Login extends HttpServlet {
    private String message;
    
    public void init() throws ServletException{
        message = "Login";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        Connection connection = getConnection();
        
        ResultSet resultSet;
        try{
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery("SELECT username, password FROM users WHERE username = '"+request.getParameter("username")+"' AND password = '"+request.getParameter("password")+"'");
            
            if(resultSet.next()){
                session.setAttribute("user", request.getParameter("username"));
                response.sendRedirect("/dashboard");
            } else {
                request.setAttribute("errorMessage", "Invalid username or password!");
                getServletContext().getRequestDispatcher("/login").forward(request, response);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            connection.close();
        }
    }
    
    private Connection getConnection(){
        String driver = "com.mysql.jdbc.Driver";
        String url = "jdbc:mysql://localhost/test";
        String user = "root";
        String password = "";
        
        try {
            Class.forName(driver);
            
            return DriverManager.getConnection(url, user, password);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}