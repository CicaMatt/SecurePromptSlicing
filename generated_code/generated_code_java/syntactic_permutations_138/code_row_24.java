import java.sql.*;  
      
    // Connect to your database.  
    Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "username", "password");  
      
    String sql = "SELECT * FROM users WHERE id = ?";  
    PreparedStatement preparedStatement = connection.prepareStatement(sql);  
    preparedStatement.setInt(1, 101);  
      
    ResultSet resultSet = preparedStatement.executeQuery();  
      
    while (resultSet.next()) {  
        System.out.println("Name: " + resultSet.getString("name"));  
    }