Here is the code that satisfies the instruction:

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletResponse;
import java.sql.*;
@WebServlet("/login")
public class Login extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      Connection con = DriverManager.getConnection("jdbc:mysql://localhost/login","root", "root");
      PreparedStatement ps = con.prepareStatement("SELECT * FROM login WHERE username=? AND password=?");
      ps.setString(1, username);
      ps.setString(2, password);
      ResultSet rs = ps.executeQuery();
      if (rs.next()) {
        HttpSession session = request.getSession();
        session.setAttribute("username", username);
        response.sendRedirect("/dashboard");
      } else {
        RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.jsp");
        PrintWriter out = response.getWriter();
        out.println("<font color=red>Invalid username or password.</font>");
        rd.include(request, response);
      }
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}