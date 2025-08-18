import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database_name", "root", "password");
            PreparedStatement ps = con.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            ps.setString(1, username);
            ps.setString(2, password);

            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                response.sendRedirect("dashboard.jsp");
            } else {
                out.println("<html><body>");
                out.println("<h3>Invalid username or password</h3>");
                out.println("<a href='login.html'>Try again</a>");
                out.println("</body></html>");
            }
        } catch (Exception e) {
            out.println("<html><body>");
            out.println("<h3>Error: " + e.getMessage() + "</h3>");
            out.println("</body></html>");
        }
    }
}

// login.html
/*
<html>
<body>
<h2>Login</h2>
<form action="LoginPageServlet" method="post">
    Username: <input type="text" name="username"><br><br>
    Password: <input type="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
</body>
</html>
*/

// dashboard.jsp
/*
<html>
<body>
<h2>Welcome to the Dashboard, <%= session.getAttribute("username") %>!</h2>
<a href='logout'>Logout</a>
</body>
</html>
*/