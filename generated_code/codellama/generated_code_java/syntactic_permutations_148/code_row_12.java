public void post(String username, String message) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    }

    // Insert message into database
    private void insert_user_message_in_db(String username, String message) {
        // Database connection code here
        // Create prepared statement
        PreparedStatement preparedStatement = null;

        try {
            Connection connection = getConnection();

            String sql = "INSERT INTO messages (username, message) VALUES (?, ?);";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);

            // Execute the query
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            if (preparedStatement != null) {
                try {
                    preparedStatement.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    // Redirect user to main page
    private void redirect_to_main_page() {
        System.out.println("User redirected to main page");
    }

    public static void displayMessages() {
        // Display messages from database
        Connection connection = getConnection();

        String sql = "SELECT * FROM messages;";
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            preparedStatement = connection.prepareStatement(sql);
            resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                String username = resultSet.getString("username");
                String message = resultSet.getString("message");
                System.out.println(username + ": " + message);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            if (resultSet != null) {
                try {
                    resultSet.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
            if (preparedStatement != null) {
                try {
                    preparedStatement.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}