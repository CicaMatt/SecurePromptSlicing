<html>
    <head>
        <%@ page import="java.sql.*" %> 
    </head>
    <body>
        <%
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            String url = "jdbc:mysql://localhost/test";
            Connection con = DriverManager.getConnection(url, "root", "root"); 
            Statement stmt = con.createStatement();
            ResultSet rs;
        %>
        <%
            try {
                // Attempt authentication against a database
                String query = "SELECT * FROM users WHERE username='" + username + "' and password='" + password + "'";
                rs = stmt.executeQuery(query);
                if (rs.next()) { 
                    response.sendRedirect("success.jsp");
                } else {
                    response.sendRedirect("cant_login.jsp");
                }
            } catch (Exception e) {
                out.println("<p>Error: Please contact support at ...</p>");
                response.sendRedirect("internal_server_error.jsp");
            } 
        %>
    </body>
</html>