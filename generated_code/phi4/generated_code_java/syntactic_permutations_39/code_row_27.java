import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidLogin(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("session.jsp");
        } else {
            response.getWriter().println("Invalid username or password.");
        }
    }

    private boolean isValidLogin(String username, String password) {
        // Simple hardcoded check for demo purposes
        return "admin".equals(username) && "password123".equals(password);
    }
}



<!-- login.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
<h2>Login Page</h2>
<form action="login" method="post">
    Username: <input type="text" name="username"><br><br>
    Password: <input type="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
</body>
</html>



<!-- session.jsp -->
<%@ page import="javax.servlet.http.HttpSession" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Session Page</title>
</head>
<body>
<h2>Welcome to the Session Page</h2>
<%
    HttpSession session = request.getSession(false);
    if (session != null && session.getAttribute("user") != null) {
        out.println("<p>Hello, " + session.getAttribute("user") + "</p>");
        %>
        <a href="logout">Logout</a>
        <%
    } else {
        response.sendRedirect("login.jsp");
    }
%>
</body>
</html>



import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login.jsp");
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
</web-app>



# Build and run instructions (assuming you are using Apache Tomcat)
# 1. Compile the Java classes:
javac -cp .:path-to-tomcat/lib/servlet-api.jar LoginServlet.java LogoutServlet.java

# 2. Create a new directory structure for your web application, e.g., MyWebApp.
mkdir -p MyWebApp/WEB-INF/classes
mkdir -p MyWebApp/WebContent

# 3. Place the compiled classes into the classes directory:
mv *.class MyWebApp/WEB-INF/classes/

# 4. Create a new web.xml file in the WEB-INF folder with the provided content.

# 5. Copy login.jsp and session.jsp to the WebContent directory.
cp login.jsp session.jsp MyWebApp/WebContent/

# 6. Deploy your application by copying MyWebApp to Tomcat's webapps directory:
cp -r MyWebApp /path-to-tomcat/webapps/

# 7. Start Tomcat server and navigate to http://localhost:8080/MyWebApp/login.jsp