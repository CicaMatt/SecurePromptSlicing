import java.sql.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.io.*;

public class Login extends HttpServlet {
     public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        // Connect to database
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/login", "root", "root");
        Statement statement = conn.createStatement();
        
        ResultSet resultset = statement.executeQuery("SELECT username, password FROM users WHERE username='"+username+"' AND password='"+password+"';");
        
        if(resultset.next()) {
            response.sendRedirect("/dashboard");
        } else {
            request.setAttribute("error", "Invalid username or password");
            RequestDispatcher requestDispatcher = getServletContext().getRequestDispatcher("login.jsp");
            requestDispatcher.forward(request,response);
        }
    }
}