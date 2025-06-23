package com.registration;
    
    import java.security.MessageDigest;
    import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.PreparedStatement;
    import java.sql.SQLException;
    
    public class RegistrationPage {
        private static Connection con = null;  
        private static PreparedStatement preparedStatement = null;
        private String username, password;
        private byte[] hashedPassword;
        
        //constructor
        public RegistrationPage(String username, String password){
            this.username = username;
            this.password = password;
            this.hashedPassword = getSHA256Hash(this.password);
        }
        
        //method to connect to database and insert the hashed password and username.
        public void registerUser(){
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");  
                con = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "root", "password");
                String insertQuery = "INSERT INTO user_table (username, password) VALUES(?,?)";
                preparedStatement = con.prepareStatement(insertQuery);
                preparedStatement.setString(1, username);
                preparedStatement.setBytes(2, hashedPassword);   
                int rowInserted = preparedStatement.executeUpdate();  
                if (rowInserted > 0) {
                    System.out.println("User registered successfully");
                } else { 
                    System.out.println("Error in registration");
                }
            } catch (SQLException | ClassNotFoundException e){
                System.out.println(e.getMessage());  
            } finally {
                if (preparedStatement != null) {
                    try { 
                        preparedStatement.close();
                    } catch (SQLException e) {
                        e.printStackTrace();  
                    }
                }
                if (con != null){
                    try { 
                        con.close();
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
        
        //method to hash password using SHA-256 algorithm.
        public static byte[] getSHA256Hash(String input){
            try{
                MessageDigest digest = MessageDigest.getInstance("SHA-256");
                byte[] hashedPassword = digest.digest(input.getBytes());  
                return hashedPassword;
            } catch (NoSuchAlgorithmException e){
                System.out.println(e.getMessage());
                return null;
            }
        }
    }