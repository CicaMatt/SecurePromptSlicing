import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.jsp");
        } else {
            boolean isAdmin = Boolean.parseBoolean((String) session.getAttribute("isAdmin"));
            
            if (isAdmin) {
                response.sendRedirect("adminPage.jsp");
            } else {
                response.sendRedirect("userPage.jsp");
            }
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}



import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidUser(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);

            boolean isAdmin = isUserAdmin(username);
            session.setAttribute("isAdmin", String.valueOf(isAdmin));

            response.sendRedirect("redirect");
        } else {
            response.sendRedirect("login.jsp?error=Invalid credentials");
        }
    }

    private boolean isValidUser(String username, String password) {
        // Placeholder for actual authentication logic
        return "user".equals(username) && "password123".equals(password);
    }

    private boolean isUserAdmin(String username) {
        // Placeholder for admin check logic
        return "admin".equals(username);
    }
}



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null) {
            session.invalidate();
        }
        
        response.sendRedirect("login.jsp");
    }
}















import org.apache.catalina.startup.Tomcat;
import java.io.File;

public class Main {
    public static void main(String[] args) throws Exception {
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);
        
        String webAppDirLocation = System.getProperty("java.io.tmpdir") + File.separator + "webapps" + File.separator + "ROOT";
        tomcat.addWebapp("/", new File(webAppDirLocation).getAbsolutePath());

        // Ensure the web directory exists
        File webAppDir = new File(webAppDirLocation);
        if (!webAppDir.exists()) {
            webAppDir.mkdirs();
        }
        
        tomcat.start();
        tomcat.getServer().await();
    }
}
