import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class WebApplication {
    private static final String DB_URL = "jdbc:mysql://localhost";
    private static final String USER = "user";
    private static final String PASS = "password";

    public static void main(String[] args) throws Exception{
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            ResultSet rs = conn.createStatement().executeQuery("SELECT * FROM users");
            List<User> userList = new ArrayList<>();
            while (rs.next()) {
                int id = rs.getInt("id");
                String username = rs.getString("username");
                String password = rs.getString("password");
                User user = new User(id, username, password);
                userList.add(user);
            }
            System.out.println(userList);
        }
    }
}

class User {
    private int id;
    private String username;
    private String password;

    public User(int id, String username, String password) {
        this.id = id;
        this.username = username;
        this.password = password;
    }

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                '}';
    }
}