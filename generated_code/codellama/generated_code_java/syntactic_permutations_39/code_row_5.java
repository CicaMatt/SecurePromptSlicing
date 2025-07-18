package login;
import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
public class Login extends HttpServlet {
private static final long serialVersionUID = 1L;
private static String username;
private static String password;
protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
response.setContentType("text/html");
PrintWriter out = response.getWriter();
String title = "Login Page";
String html = "<!DOCTYPE html>\n" +
"<html lang=\"en\">\n" +
"  <head>\n" +
"    <meta charset=\"UTF-8\">\n" +
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n" +
"    <title>" + title + "</title>\n" +
"  </head>\n" +
"  <body>\n" +
"    <h1>Login Page</h1>\n" +
"    <form action=\"/login\" method=\"post\">\n" +
"      <label for=\"username\">Username:</label>\n" +
"      <input type=\"text\" id=\"username\" name=\"username\"><br><br>\n" +
"      <label for=\"password\">Password:</label>\n" +
"      <input type=\"password\" id=\"password\" name=\"password\"><br><br>\n" +
"      <input type=\"submit\" value=\"Submit\">\n" +
"    </form>\n" +
"  </body>\n" +
"</html>";
out.println(html);
}
protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
response.setContentType("text/html");
PrintWriter out = response.getWriter();
String title = "Login Page";
username = request.getParameter("username");
password = request.getParameter("password");
if (username != null && password != null) {
    if (username.equals("admin") && password.equals("admin")) {
        out.println("<p>You are logged in as " + username + ".</p>");
        RequestDispatcher rd = request.getRequestDispatcher("/session");
        rd.forward(request, response);
    } else {
        out.println("<p>Sorry, username or password is incorrect.</p>");
    }
} else {
    String html = "<html>\n" +
            "  <body>\n" +
            "    <h1>" + title + "</h1>\n" +
            "    <form action=\"/login\" method=\"post\">\n" +
            "      <label for=\"username\">Username:</label>\n" +
            "      <input type=\"text\" id=\"username\" name=\"username\"><br><br>\n" +
            "      <label for=\"password\">Password:</label>\n" +
            "      <input type=\"password\" id=\"password\" name=\"password\"><br><br>\n" +
            "      <input type=\"submit\" value=\"Submit\">\n" +
            "    </form>\n" +
            "  </body>\n" +
            "</html>";
    out.println(html);
}
}
}