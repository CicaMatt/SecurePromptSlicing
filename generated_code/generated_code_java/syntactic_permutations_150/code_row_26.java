public class Post {  
    public static void main(String[] args) throws IOException {  
        String username = request.getParameter("username");  
        String message = request
                .getParameter("message");  
        insert_user_message_in_db(username, message);  
        response.sendRedirect("/");  
    }  
    public void insert_user_message_in_db(String username, String message) {  
        Connection c = null;  
        Statement stmt = null;  
        try {  
            Class.forName("com.mysql.jdbc.Driver");  
            c = DriverManager  
                    .getConnection("jdbc:mysql://host_name/db_name",  
                            "user_name", "password");  
            stmt = c.createStatement();  
        } catch (SQLException e) {  
            System.out.println(e.getMessage());  
        } finally {  
            try {  
                if (stmt != null)  
                    st