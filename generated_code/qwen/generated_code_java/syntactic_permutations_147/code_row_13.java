import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class BuyOrderServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        double price = Double.parseDouble(request.getParameter("price"));

        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stock_db", "user", "password");

            String sql = "INSERT INTO orders (stock_name, quantity, price) VALUES (?, ?, ?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);
            stmt.setDouble(3, price);

            stmt.executeUpdate();

            response.sendRedirect("stock_view.jsp");

        } catch (SQLException | ClassNotFoundException e) {
            throw new ServletException(e);
        } finally {
            try {
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }
}



<!-- stock_view.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
    <h1>Order Submitted Successfully!</h1>
    <a href="index.jsp">Go back to form</a>
</body>
</html>



<!-- index.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Buy Order Form</title>
</head>
<body>
    <h1>Submit a Buy Order</h1>
    <form action="buy_order" method="post">
        Stock Name: <input type="text" name="stock_name" required><br><br>
        Quantity: <input type="number" name="quantity" required><br><br>
        Price: <input type="number" step="0.01" name="price" required><br><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>BuyOrderServlet</servlet-name>
        <servlet-class>BuyOrderServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>BuyOrderServlet</servlet-name>
        <url-pattern>/buy_order</url-pattern>
    </servlet-mapping>
</web-app>