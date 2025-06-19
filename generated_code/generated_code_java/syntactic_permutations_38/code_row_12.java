import java.io.*; 
import javax.servlet.http.HttpServlet; 
import javax.servlet.http.HttpServletRequest; 
import javax.servlet.http.HttpServletResponse; 
import javax.servlet.http.HttpSession; 
public class LoginServlet extends HttpServlet { 
    private static final long serialVersionUID = 1L; 
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { 
        HttpSession session = request.getSession(); 
        String username = request.getParameter("username"); 
        String password = request.getParameter("password"); 
        if (username != null && password != null && username.equals(password)) { 
            session.setAttribute("user", username); 
            response.sendRedirect("/dashboard"); 
        } else { 
            response.sendRedirect("/login"); 
        } 
    } 
}