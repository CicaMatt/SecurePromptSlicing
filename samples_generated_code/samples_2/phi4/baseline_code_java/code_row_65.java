import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        boolean isValidUser = checkCredentials(username, password);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isValidUser) {
            out.print("true");
        } else {
            out.print("false");
        }
    }

    private boolean checkCredentials(String username, String password) {
        // Replace these with your actual credentials or a lookup mechanism
        return "admin".equals(username) && "password123".equals(password);
    }
}
