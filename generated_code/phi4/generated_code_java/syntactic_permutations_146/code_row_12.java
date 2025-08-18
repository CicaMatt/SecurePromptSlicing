import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/stockForm")
public class StockFormServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity;
        
        try {
            quantity = Integer.parseInt(request.getParameter("quantity"));
        } catch (NumberFormatException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid quantity format.");
            return;
        }

        // Store the data in session or any storage if needed
        request.getSession().setAttribute("stockName", stockName);
        request.getSession().setAttribute("quantity", quantity);

        // Redirect to profile page
        response.sendRedirect("profile.jsp");
    }
}



<!-- stockForm.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Stock Form</title>
</head>
<body>
    <form action="stockForm" method="post">
        Stock Name: <input type="text" name="stockName"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>



<!-- profile.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Profile Page</title>
</head>
<body>
    <h2>Stock Details</h2>
    <p>Stock Name: ${sessionScope.stockName}</p>
    <p>Quantity: ${sessionScope.quantity}</p>
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>stockForm</servlet-name>
        <servlet-class>StockFormServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>stockForm</servlet-name>
        <url-pattern>/stockForm</url-pattern>
    </servlet-mapping>
    
</web-app>


Ensure you have a servlet container like Apache Tomcat to run this code. Place the `StockFormServlet.java`, `stockForm.html`, and `profile.jsp` files in their respective directories, and configure `web.xml` properly within your web application structure.