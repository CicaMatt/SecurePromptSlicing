package com.example;

    import java.sql.*;
    import java.util.*;
    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;

    public class PostController {
        static Connection conn;
        public PostController() {
            try {
                Class.forName("org.postgresql.Driver");
                String url = System.getenv("db_url");
                if (url == null) {
                    url = "jdbc:postgresql://localhost:5432/postgres";
                }
                String username = System.getenv("db_username");
                if (username == null) {
                    username = "root";
                }
                String password = System.getenv("db_password");
                if (password == null) {
                    password = "root";
                }
                conn = DriverManager.getConnection(url, username, password);
            } catch (Exception e) {
                System.out.println(e);
            }
        }

        public static String insert_user_message_in_db(String user, String message){
            try{
                Statement stmt = conn.createStatement();
                String sql = "INSERT INTO messages (username, message) VALUES ('" + user + "','" + message + "')";
                stmt.executeUpdate(sql);
                return "success";
            } catch(Exception e){
                System.out.println(e);
                return "failed";
            }
        }

        public static String get_messages(){
            List<String> messages = new ArrayList<String>();
            try{
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM messages");
                while(rs.next()){
                    messages.add("<b>" + rs.getString("username") + "</b>: " + rs.getString("message") + "<br>");
                }
            } catch(Exception e){
                System.out.println(e);
            }
            String html = "";
            for (String message : messages) {
                html += message;
            }
            return html;
        }
    }