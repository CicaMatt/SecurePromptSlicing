import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
 
public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request,
                          HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username != null && username.equalsIgnoreCase("admin")
                && password != null && password.equalsIgnoreCase("password")) {
            HttpSession session = request.getSession(true);
            session.setAttribute("username", "admin");
            response.sendRedirect("secret.jsp");
        } else {
            RequestDispatcher rd = getServletContext()
                    .getRequestDispatcher("/login.html");
            PrintWriter out = response.getWriter();
            out.println("<font color=red>Error: Invalid login</font>");
            rd.include(request, response);
        }
    }
}