import java.util.*;
    public class Login {
      public void login(String username, String password) throws Exception {
        Connection connection = getConnection();
        PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username = ?");
        statement.setString(1,username);
        ResultSet resultSet = statement.executeQuery();
        if (resultSet.next()) {
          String dbPassword = resultSet.getString("password");
          if (dbPassword.equals(password)) {
            redirectToHomePage();
          } else {
            return;
          }
        } else {
          return;
        }
      }
    }