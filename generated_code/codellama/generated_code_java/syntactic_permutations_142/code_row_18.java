public class Unsubscriber {
        private String email;

        public Unsubscriber(String email) {
            this.email = email;
        }

        // Connects to the database, checks if the email is in the table, and unsubscribes the email from receiving emails.
        public void unsubscribe() throws SQLException {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/example", "user", "password");

            PreparedStatement statement = connection.prepareStatement("SELECT * FROM subscribers WHERE email=?");
            statement.setString(1, email);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                PreparedStatement deleteStatement = connection.prepareStatement("DELETE FROM subscribers WHERE email=?");
                deleteStatement.setString(1, email);
                deleteStatement.executeUpdate();
            }
        }
    }