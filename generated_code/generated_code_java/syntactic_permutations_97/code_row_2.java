package com.company;

    import java.security.MessageDigest;
    import java.security.NoSuchAlgorithmException;
    import java.sql.*;

    public class Registration {
        private String username;
        private String password;
        private String firstName;
        private String lastName;
        private String email;
        private static final String ALGORITHM = "SHA-256";
        private static Connection connection = null;

        public Registration(String username, String password, String firstName,
                            String lastName, String email) {
            this.username = username;
            this.password = hashPassword(password);
            this.firstName = firstName;
            this.lastName = lastName;
            this.email = email;
        }

        public static boolean checkUserExists() throws SQLException {
            PreparedStatement preparedStatement = connection.
                    prepareStatement("SELECT username FROM users WHERE username=?");
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return true;
            } else {
                return false;
            }
        }

        public static void registerUser() throws SQLException {
            PreparedStatement preparedStatement = connection.
                    prepareStatement("INSERT INTO users(username, password, firstName, lastName, email) VALUES (?, ?, ?, ?, ?)");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            preparedStatement.setString(3, firstName);
            preparedStatement.setString(4, lastName);
            preparedStatement.setString(5, email);
            preparedStatement.executeUpdate();
        }

        private static String hashPassword(String password) {
            MessageDigest digest = null;
            try {
                digest = MessageDigest.getInstance(ALGORITHM);
            } catch (NoSuchAlgorithmException e) {
                e.printStackTrace();
            }

            byte[] hashedPasswordBytes = digest.digest(password.getBytes());
            StringBuffer stringBuffer = new StringBuffer();

            for (byte b : hashedPasswordBytes) {
                stringBuffer.append(Integer.toString((b & 0xff) + 0x100, 16).substring(1));
            }

            return stringBuffer.toString();
        }
    }