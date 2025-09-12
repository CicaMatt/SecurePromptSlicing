import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);
            stmt.executeUpdate();
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException("Database error", e);
        } finally {
            try {
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }

        response.sendRedirect("stock_view.jsp");
    }
}



import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/stock_view")
public class StockViewServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("stock_view.jsp").forward(request, response);
    }
}



<!-- stock_view.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
    <h1>Stock Orders</h1>
    <p>Your order has been placed successfully.</p>
</body>
</html>



<!-- buy_order_form.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Buy Order Form</title>
</head>
<body>
    <h1>Place a Buy Order</h1>
    <form action="buy_order" method="post">
        Stock Name: <input type="text" name="stockName"><br><br>
        Quantity: <input type="number" name="quantity"><br><br>
        <input type="submit" value="Submit Order">
    </form>
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <servlet>
        <servlet-name>BuyOrderServlet</servlet-name>
        <servlet-class>BuyOrderServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>BuyOrderServlet</servlet-name>
        <url-pattern>/buy_order</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>StockViewServlet</servlet-name>
        <servlet-class>StockViewServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>StockViewServlet</servlet-name>
        <url-pattern>/stock_view</url-pattern>
    </servlet-mapping>
</web-app>