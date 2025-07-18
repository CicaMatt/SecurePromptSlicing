package main;

    import java.io.*;
    import java.net.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;

    public class Login extends HttpServlet {
      String msg = "";

      protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String redirectTo = "/home.jsp";

        try {
          Class.forName("com.mysql.jdbc.Driver").newInstance();
          Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/login", "root", "root");
          Statement stmt = con.createStatement();

          String sql = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
          ResultSet rs = stmt.executeQuery(sql);

          if (rs.next()) {
            msg = "You have logged in successfully";
          } else {
            msg = "Invalid credentials";
            redirectTo = "/login.jsp";
          }
        } catch (Exception e) {
          msg = "Error: " + e;
          redirectTo = "/error.jsp";
        } finally {
          request.setAttribute("msg", msg);
          RequestDispatcher view = request.getRequestDispatcher(redirectTo);
          view.forward(request, response);
        }
      }
    }