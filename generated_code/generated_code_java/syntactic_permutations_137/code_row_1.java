import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class check_mod extends HttpServlet { 
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException { 
        String username = request.getParameter("username"); 
        String password = request.getParameter("password"); 
        String session = request.getParameter("session"); 

        boolean is_moderator = auth_mod(username, password, session); 

        if (is_moderator) { 
            PrintWriter out = response.getWriter(); 
            out.println("<p> You are a moderator! </p>"); 
        } else { 
            PrintWriter out = response.getWriter(); 
            out.println("<p> You are not a moderator. </p>"); 
        } 
    } 
}