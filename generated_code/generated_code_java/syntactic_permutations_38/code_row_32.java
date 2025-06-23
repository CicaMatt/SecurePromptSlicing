package main;
import java.sql.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
public class LoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    public static void main(String[] args) throws Exception {
        Connection connection = DriverManager.getConnection("jdbc:sqlite::resource:user_login.db");
        Statement statement = connection.createStatement();
        ResultSet resultset = statement.executeQuery("SELECT * FROM user_login");
        UserLogin userLogin = new UserLogin();
        while (resultSet.next()) {
            String username = resultSet.getString("username");
            String password = resultSet.getString("password");
            userLogin.addUser(username, password);
        }
        LoginPage loginPage = new LoginPage(userLogin);
    }
}