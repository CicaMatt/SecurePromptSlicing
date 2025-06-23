import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.sql.*;

@WebServlet(name = "LoginPage", urlPatterns = {"/login"})
public class LoginPage extends HttpServlet {
   @Override
   protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
       // Set the MIME type for the response message
      response.setContentType("text/html");
      // Get a output writer to write the response message
      PrintWriter out = response.getWriter();
      // Print an HTML page as the output of the servlet
      out.println("<html>");
      out.println("<head><title>Login Page</title></head>");
      out.println("<body>");
      out.println("<form method=\"post\">");
      out.println("Username:<br>");
      out.println("<input type=\"text\" name=\"username\" size=\"20\"><br>");
      out.println("Password:<br>");
      out.println("<input type=\"password\" name=\"password\" size=\"20\"><br><br>");
      out.println("<input type=\"submit\" value=\"Login\">");
      out.println("</form>");
      out.println("</body>");
      out.println("</html>");
   }

   @Override
   protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
       // Get the username and password from the form data
       String username = request.getParameter("username");
       String password = request.getParameter("password");
       Connection conn = null; // To connect to the database
       Statement stmt = null; // To create SQL statements
       ResultSet rs = null; // To get data from the database
       // Connect to the database
       try {
           // Load JDBC driver
           Class.forName("com.mysql.jdbc.Driver");
           System.out.println("JDBC Driver loaded successfully.");
           conn = DriverManager.getConnection(
             "jdbc:mysql://localhost:3306/TestDB",
             "root", //username
             "root"  //password
            );
           stmt = conn.createStatement();
           System.out.println("Connected to database");
           // check if username and password are in the database
           rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
           if (rs.next()) {
               response.sendRedirect("success.html");
           } else {
               response.sendRedirect("cant_login.html");
           }
       } catch (Exception e) {
           System.out.println(e);
           response.sendRedirect("internal_server_error.html");
       } finally {
           try {
               // Close the statement and the connection
               if (stmt != null) stmt.close();
               if (conn != null) conn.close();
            } catch (SQLException e) {
                System.out.println(e);
             }
       }
   }
}