import java.sql.*;
import spark.Spark;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpServletRequest;
import com.google.gson.Gson;

public class Main {
  static final int port = 4567;
   
    public static void main(String[] args) {
        Spark.port(port);
        Spark.get("/isModerator", (req, res) -> isModerator((HttpServletRequest) req, (HttpServletResponse) res));
    }
   
  private static String isModerator(HttpServletRequest req, HttpServletResponse resp) {
      String userName = req.getParameter("user");
      try {
          Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost/mydb", "username", "password");
          PreparedStatement statement = connection.prepareStatement("SELECT isModerator FROM users WHERE username = ?;");
          statement.setString(1, userName);
          ResultSet result = statement.executeQuery();
          if (result.next()) {
              return result.getString(1);
          } else {
              resp.setStatus(HttpServletResponse.SC_NOT_FOUND);
              return null;
          }
      } catch (SQLException e) {
          resp.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
          return null;
      }
    }
}