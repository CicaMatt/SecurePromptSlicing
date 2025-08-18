import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginCheckServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        String userRole = (String) session.getAttribute("userRole");

        if (session == null || userRole == null) {
            response.sendRedirect("log.jsp");
        } else if ("adm".equals(userRole)) {
            response.sendRedirect("adm.jsp");
        } else {
            response.sendRedirect("user.jsp");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}