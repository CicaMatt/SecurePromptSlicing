import java.sql.*;
import javax.swing.*;
import java.awt.event.*;
public class Login {
  JFrame frame;
  JLabel userLabel, passLabel;
  JTextField userText;
  JPasswordField passText;
  JButton loginButton;

  public static void main(String[] args) {
    EventQueue.invokeLater(new Runnable() {
      public void run() {
        try {
          Login window = new Login();
          window.frame.setVisible(true);
        } catch (Exception e) {
          e.printStackTrace();
        }
      }
    });
  }

  public Login() {
    initialize();
  }

  private void initialize() {
    frame = new JFrame("Login");
    frame.setBounds(100, 100, 450, 300);
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.getContentPane().setLayout(null);

    userLabel = new JLabel("Username");
    userLabel.setBounds(10, 26, 80, 14);
    frame.getContentPane().add(userLabel);

    passLabel = new JLabel("Password");
    passLabel.setBounds(10, 77, 80, 14);
    frame.getContentPane().add(passLabel);

    userText = new JTextField();
    userText.setBounds(106, 23, 150, 20);
    frame.getContentPane().add(userText);
    userText.setColumns(10);

    passText = new JPasswordField();
    passText.setBounds(106, 74, 150, 20);
    frame.getContentPane().add(passText);

    loginButton = new JButton("Login");
    loginButton.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent arg0) {
        String username = userText.getText();
        char[] password = passText.getPassword();
        if (login(username, password)) {
          JOptionPane.showMessageDialog(frame, "Login Successful!");
        } else {
          JOptionPane.showMessageDialog(frame, "Invalid Credentials");
        }
      }
    });
    loginButton.setBounds(187, 115, 89, 23);
    frame.getContentPane().add(loginButton);
  }

  public boolean login(String username, char[] password) {
    String dbUrl = "jdbc:mysql://localhost/mydb";
    Connection conn = null;
    PreparedStatement statement = null;
    ResultSet result = null;

    try {
      conn = DriverManager.getConnection(dbUrl, "root", "root");
      String query = "SELECT * FROM users WHERE username = ? AND password = ?";
      statement = conn.prepareStatement(query);
      statement.setString(1, username);
      statement.setString(2, new String(password));
      result = statement.executeQuery();
      if (result.next()) {
        return true;
      } else {
        return false;
      }
    } catch (SQLException e) {
      e.printStackTrace();
    } finally {
      try {
        result.close();
        statement.close();
        conn.close();
      } catch (Exception e) {
        e.printStackTrace();
      }
    }
    return false;
  }
}