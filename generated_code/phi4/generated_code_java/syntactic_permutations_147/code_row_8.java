import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stocks";
    private static final String USER = "root";
    private static final String PASS = "password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO orders (stock_name) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, stockName);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            throw new ServletException("Database connection problem", e);
        }

        response.sendRedirect("stock_view");
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class StockOrderFormServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head><title>Order Stock</title></head>");
            out.println("<body>");
            out.println("<form action='buy_order' method='post'>");
            out.println("Stock Name: <input type='text' name='stock_name'><br>");
            out.println("<input type='submit' value='Submit Order'>");
            out.println("</form>");
            out.println("</body>");
            out.println("</html>");
        }
    }
}


Note: This code assumes you have a MySQL database set up with the necessary driver in your classpath and a table named `orders` with at least one column `stock_name`. You should replace the database URL, username, and password with appropriate values for your environment. Also, ensure that the servlet container (e.g., Apache Tomcat) is properly configured to run this code.