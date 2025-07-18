import java.sql.*;  
      
    public class Database {  
        // JDBC driver name and database URL  
        static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
        static final String DB_URL = "jdbc:mysql://localhost/EMP";  
        
        //  Database credentials  
        static final String USER = "username";  
        static final String PASS = "password";  
      
        public static void upload_image(String imageName, byte[] imageData) {  
            Connection conn = null;  
            PreparedStatement preparedStatement = null;  
            try {  
                //STEP 2: Register JDBC driver  
                Class.forName("com.mysql.jdbc.Driver");  
      
                //STEP 3: Open a connection  
                System.out.println("Connecting to database...");  
                conn = DriverManager.getConnection(DB_URL, USER, PASS);  
      
                //STEP 4: Execute a query  
                System.out.println("Creating statement...");  
                String sql = "INSERT INTO images (name, data) VALUES (?, ?)";  
                preparedStatement = conn.prepareStatement(sql);  
                preparedStatement.setString(1, imageName);  
                preparedStatement.setBytes(2, imageData);  
                System.out.println("Inserting record...");  
                int row = preparedStatement.executeUpdate();  
                if (row == 1) {  
                    System.out.println("Record inserted successfully.");  
                } else {  
                    System.out.println("Error inserting record.");  
                }  
            } catch (SQLException e) {  
                throw new IllegalStateException("Something went wrong: " + e.getMessage(), e);  
            } finally {  
                if (preparedStatement != null) {  
                    try {  
                        preparedStatement.close();  
                    } catch (SQLException ex) {  
                        System.out.println(ex.getMessage());  
                    }  
                }  
                if (conn != null) {  
                    try {  
                        conn.close();  
                    } catch (SQLException ex) {  
                        System.out.println(ex.getMessage());  
                    }  
                }  
            }  
      
        }  
      
    }