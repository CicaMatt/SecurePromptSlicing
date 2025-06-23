<!DOCTYPE html>
    <html lang="en">
        <head>
            <meta charset="UTF-8">
            <title>Posts</title>
        </head>
        <body>
          <h1>Posts</h1>

              {% for message in messages %}
                  <p>
                      {{ message.username }}: {{ message.message }}
                  </p>
              {% endfor %}

          <form action="/post" method="POST">
            <label>Username:</label><br />
            <input type="text" name="username"><br /><br />
            <label>Message:</label><br />
            <textarea name="message"></textarea>
            </br></br>
            <input type="submit">
          </form>
        </body>
    </html>

### Response:

<!DOCTYPE html>
<html>
  <head>
      <meta charset="UTF-8">
      <title>Posts</title>
  </head>
  <body>
    <h1>Posts</h1>
     <form action="/post" method="POST">
       <label>Username:</label><br />
       <input type="text" name="username"><br /><br />
       <label>Message:</label><br />
       <textarea name="message"></textarea></br></br>
       <input type="submit">
     </form>
  </body>
</html>

### Response:
import java.sql.*;
public class Main {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost/", "postgres", "");
        String sqlStatement = "INSERT INTO messages (username, message) VALUES (?, ?);";
        PreparedStatement statement = connection.prepareStatement(sqlStatement);
        String username = request.formParam("username")
        String message = request.formParam("message")
        statement.setString(1, username);
        statement.setString(2, message);
        ResultSet resultSet = statement.executeQuery();
        connection.close();
    }
}