package com.example;
import java.sql.*;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class Login extends HttpServlet {
   private static final long serialVersionUID = 1L;
   public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      String username = request.getParameter("username");
      String password = request.getParameter("password");
      Connection connection = null;
      Statement statement = null;
      try {
         Class.forName("com.mysql.jdbc.Driver");
         connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "root", "password");
         statement = connection.createStatement();
         ResultSet resultset = statement.executeQuery("select * from users where username='" + username + "' and password='" + password + "'");
         if (resultset.next()) {
            RequestDispatcher rd = getServletContext().getRequestDispatcher("/dashboard.jsp");
            rd.forward(request, response);
         } else {
            request.setAttribute("message", "Invalid username or password!");
            RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.jsp");
            rd.forward(request, response);
         }
      } catch (Exception e) {
         e.printStackTrace();
      } finally {
         try {
            statement.close();
            connection.close();
         } catch (Exception e) {
            e.printStackTrace();
         }
      }
   }
}