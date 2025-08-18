import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class BuyOrderServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "username", "password");

            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);

            stmt.executeUpdate();

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        response.sendRedirect("stock_view.jsp");
    }
}



<!-- buy_form.jsp -->
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
    <h2>Buy Stock Form</h2>
    <form action="buy_order" method="post">
        Stock Name: <input type="text" name="stockName"><br><br>
        Quantity: <input type="number" name="quantity"><br><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>



<!-- stock_view.jsp -->
<html>
<head>
    <title>Stock View</title>
</head>
<body>
    <h2>Your order has been placed successfully!</h2>
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
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
    <welcome-file-list>
        <welcome-file>buy_form.jsp</welcome-file>
    </welcome-file-list>
</web-app>