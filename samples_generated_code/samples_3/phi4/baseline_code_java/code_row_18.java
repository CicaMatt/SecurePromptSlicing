import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class CheckModServlet extends HttpServlet {

    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password123";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        PrintWriter out = response.getWriter();
        response.setContentType("text/plain");

        if (checkMod(username, password)) {
            out.print("true");
        } else {
            out.print("false");
        }
    }

    private boolean checkMod(String username, String password) {
        return USERNAME.equals(username) && PASSWORD.equals(password);
    }
}


To make this servlet runnable:

1. Ensure you have a Java servlet container like Apache Tomcat installed.
2. Place the above code in a file named `CheckModServlet.java`.
3. Compile it using: `javac CheckModServlet.java`.
4. Deploy it to your servlet container, following its specific deployment instructions (usually involving placing it in a web application directory).
5. Access it via the URL pattern `/check_mod?username=<your-username>&password=<your-password>`.