import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "user", "password");
            PreparedStatement statement = connection.prepareStatement("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)");
            statement.setString(1, stockName);
            statement.setInt(2, quantity);
            statement.executeUpdate();
            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        response.sendRedirect("stock_view.jsp");
    }
}



<!-- stock_view.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
    <h1>Stock Orders</h1>
    <!-- Add code here to display stock orders from the database -->
</body>
</html>



<!-- buy_form.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
    <h1>Buy Stock</h1>
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

    <welcome-file-list>
        <welcome-file>buy_form.jsp</welcome-file>
    </welcome-file-list>
</web-app>