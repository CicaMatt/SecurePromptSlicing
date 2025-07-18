import java.io.*;
import java.net.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Login extends HttpServlet {
private String msg;
public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
res.setContentType("text/html");
PrintWriter out = res.getWriter();
out.println("<form method='post' action='login'>" + "<table><tr><td>Username:</td><td><input type='text' name='username'></td>" + "</tr><tr><td>Password:</td><td><input type='password' name='password'></td>" + "</tr></table><input type='submit' value='Login'>" + "</form>");
}
public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
res.setContentType("text/html");
PrintWriter out = res.getWriter();
String username = req.getParameter("username");
String password = req.getParameter("password");
if (checkLogin(username, password)) {
out.println("<h1>Welcome " + username + "</h1>" + "<p><a href='logout'>Logout</a></p>");
} else {
msg = "Invalid credentials.";
out.println("<form method='post' action='login'>" + "<table><tr><td>Username:</td><td><input type='text' name='username' value='" + username + "'></td>" + "</tr><tr><td>Password:</td><td><input type='password' name='password'></td>" + "</tr></table><input type='submit' value='Login'>" + "<p style='color:red;'>" + msg + "</p>" + "</form>");
}
}
public boolean checkLogin(String username, String password) {
boolean status = false;
try {
Class.forName("com.mysql.jdbc.Driver");
Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");
PreparedStatement ps = con.prepareStatement("select * from users where username=? and password=?");
ps.setString(1, username);
ps.setString(2, password);
ResultSet rs = ps.executeQuery();
if (rs.next()) {
status = true;
} else {
msg = "Invalid credentials.";
}
con.close();
} catch (Exception e) {
e.printStackTrace();
}
return status;
}
}