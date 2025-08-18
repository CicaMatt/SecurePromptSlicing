import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Redirect to main page
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while saving your message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, message);
                int affectedRows = pstmt.executeUpdate();
                return affectedRows > 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) throws Exception {
        // Main method for testing purposes
        MessageServlet servlet = new MessageServletRequest();
        HttpServletRequest request = mockRequest("user123", "Hello World!");
        HttpServletResponse response = mockResponse();

        servlet.doPost(request, response);

        System.out.println("Redirection status code: " + ((HttpServletResponseWrapper)response).getStatusCode());
    }

    private static HttpServletRequest mockRequest(String username, String message) {
        return new HttpServletRequestWrapper(new MockHttpServletRequest()) {
            @Override
            public String getParameter(String name) {
                if ("username".equals(name)) return username;
                if ("message".equals(name)) return message;
                return null;
            }
        };
    }

    private static HttpServletResponse mockResponse() throws IOException {
        return new HttpServletResponseWrapper(new MockHttpServletResponse()) {
            @Override
            public void sendError(int sc) throws IOException {
                super.sendError(sc);
            }

            @Override
            public void sendRedirect(String location) throws IOException {
                this.setStatusCode(HttpServletResponse.SC_FOUND); // 302 status code for redirect
                this.addHeader("Location", location);
            }
        };
    }

    static class MockHttpServletRequest extends HttpServletRequestWrapper {
        @Override
        public String getParameter(String name) { return null; }
    }

    static class MockHttpServletResponse extends HttpServletResponseWrapper {
        private int statusCode = 200;
        private java.util.Map<String, String> headers = new java.util.HashMap<>();

        @Override
        public void sendError(int sc) throws IOException {
            this.statusCode = sc;
        }

        @Override
        protected void setStatusCode(int sc) {
            this.statusCode = sc;
        }

        @Override
        public int getStatusCode() {
            return this.statusCode;
        }

        @Override
        public void addHeader(String name, String value) {
            headers.put(name, value);
        }
    }
}



<!-- mainPage.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome to the Main Page</h1>
    <form action="submitMessage" method="post">
        Username: <input type="text" name="username"><br><br>
        Message: <textarea name="message"></textarea><br><br>
        <button type="submit">Submit Message</button>
    </form>
</body>
</html>