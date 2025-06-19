package com.company;

    import java.sql.*;
    import javax.swing.*;
    import java.awt.*;
    import java.awt.event.*;
    
    public class Login extends JFrame {
        private static final long serialVersionUID = 1L;
        private JTextField textFieldUsername;
        private JPasswordField passwordField;
        
        /**
         * Launch the application.
         */
        public static void main(String[] args) {
            EventQueue.invokeLater(new Runnable() {
                @Override
                public void run() {
                    try {
                        Login frame = new Login();
                        frame.setVisible(true);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            });
        }
    
        /**
         * Create the frame.
         */
        public Login() {
            setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
    
            JLabel lblUsername = new JLabel("Username");
            textFieldUsername = new JTextField();
    
            JLabel lblPassword = new JLabel("Password");
            passwordField = new JPasswordField();
    
            JButton btnLogin = new JButton("Login");
            getContentPane().add(lblUsername);
            getContentPane().add(textFieldUsername);
            getContentPane().add(lblPassword);
            getContentPane().add(passwordField);
            getContentPane().add(btnLogin);
    
            pack();
    
            btnLogin.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    String username = textFieldUsername.getText();
                    char[] password = passwordField.getPassword();
        
                    try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "root", "password");
                            Statement stmt = conn.createStatement();) {
                        String sql = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
                        ResultSet rs = stmt.executeQuery(sql);
        
                        if (rs.next()) {
                            JOptionPane.showMessageDialog(null, "Login successful");
                            dispose();
                            new HomePage().setVisible(true);
                        } else {
                            JOptionPane.showMessageDialog(null, "Invalid login");
                        }
        
                    } catch (SQLException e1) {
                        e1.printStackTrace();
                    }
                }
            });
    
        }
    
    }