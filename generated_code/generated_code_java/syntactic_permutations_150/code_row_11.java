import java.util.*;
    import java.text.*;
    import java.io.*;

    public class Message {
        String username;
        String message;
    	String getUsername() {return this.username;}
    	void setUsername(String value) {this.username = value;}
    	String getMessage() {return this.message;}
    	void setMessage(String value) {this.message = value;}
    }

    public class Post {
        private final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
        private final String DB_URL = "jdbc:mysql://localhost:3306/messages?useSSL=false&serverTimezone=UTC";
        private final String USER = "root";
        private final String PASS = "password";

    	public void post(String username, String message) {
            Connection conn;
            Statement stmt;

            try {
                Class.forName("com.mysql.cj.jdbc.Driver");

                System.out.println("Connecting to database...");
                conn = DriverManager.getConnection(DB_URL, USER, PASS);

                System.out.println("Creating statement...");
                stmt = conn.createStatement();

                String sql = "INSERT INTO messages (username, message) VALUES ('" + username + "', '" + message + "')";

                stmt.executeUpdate(sql);
                stmt.close();
                conn.close();
            } catch (Exception e) {
                System.out.println("Error in connection: " + e.getMessage());
            }
        }
    }

    public class MainPage {
    	public void main(String[] args){
        	String username = request.getParameter("username");
        	String message = request.getParameter("message");
        	Post post = new Post();
        	post.post(username, message);

        	response.sendRedirect("/index.html");
    	}
    }