import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String htmlForm = "<html><body>"
                + "<form action='do_login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form></body></html>";
        
        out.println(htmlForm);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isAdmin(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);

            response.sendRedirect("admin_page.jsp"); // Assuming there is a JSP page named admin_page.jsp
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            
            String errorMessage = "<html><body>"
                    + "Invalid credentials. <a href='login'>Try again</a></body></html>";
            
            out.println(errorMessage);
        }
    }

    private boolean isAdmin(String username, String password) {
        // Dummy check for admin user
        return "admin".equals(username) && "password123".equals(password);
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Admin Page</title>
</head>
<body>
<h1>Welcome to the Admin Page, <%= session.getAttribute("user") %>!</h1>
</body>
</html>


Note: This code assumes a servlet container like Apache Tomcat for deployment. The `admin_page.jsp` should be created in your web application's directory structure under `WEB-INF`. Adjust the path or filename as needed based on your project setup.