package com.company;

    import java.sql.*;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;

    public class LoginPage {
        String username, password;
        Connection conn = null;
        ResultSet rs = null;

        public void login(String uname, String pword) throws ClassNotFoundException, SQLException {
            username = uname;
            password = pword;
            connectToDatabase();
        }

        private void connectToDatabase() throws ClassNotFoundException, SQLException{
            //Load the driver.  This could also be done in the web container
            String url = "jdbc:mysql://localhost:3306/your_database_name";
            Class.forName("com.mysql.jdbc.Driver");

            conn = DriverManager.getConnection(url, "root", "password");
            String queryString = "SELECT * FROM users WHERE username = ? AND password = ?";
            PreparedStatement preparedStatement = conn.prepareStatement(queryString);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            rs = preparedStatement.executeQuery();
        }

        public boolean isLoggedIn(){
            try {
                if (rs != null && rs.next()) {
                    return true;
                } else {
                    return false;
                }
            } catch(SQLException e){
                throw new RuntimeException("Error checking if user logged in", e);
            }
        }

        public void closeDatabase() throws SQLException{
            try {
                rs.close();
                conn.close();
            } catch (SQLException e) {
                throw new RuntimeException("Error closing the database connection", e);
            }
        }
    }