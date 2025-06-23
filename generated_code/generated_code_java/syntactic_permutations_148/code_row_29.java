package com.example;

        import java.sql.*;
        import javax.servlet.*;
        import javax.servlet.http.*;

        public class Message {
            private String username;
            private String message;

            public Message(String username, String message) {
                this.username = username;
                this.message = message;
            }

            public void post() throws SQLException {
                insert_user_message_in_db();
                RequestDispatcher view = request.getRequestDispatcher("display_messages.jsp");
                view.forward(request, response);
            }

            private void insert_user_message_in_db() throws SQLException {
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection con = DriverManager.getConnection("jdbc:mysql://localhost/messages", "root", "password");
                PreparedStatement statement = con.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            }
        }