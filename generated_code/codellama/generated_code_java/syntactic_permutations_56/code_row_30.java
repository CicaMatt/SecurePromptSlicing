package code_generation;

import java.awt.*;
import javax.swing.*;
import java.sql.*;

public class LoginPage extends JFrame {
    private JPanel contentPane;
    private JTextField txtOldEmail;
    private JTextField txtNewEmail;
    private JPasswordField pswdConfirm;
    private JButton btnChangeEmail;
    private JLabel lblStatus;
    
    public LoginPage() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 450, 300);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);
        
        JLabel lblOldEmail = new JLabel("Old Email: ");
        lblOldEmail.setBounds(80, 36, 72, 14);
        contentPane.add(lblOldEmail);
        
        txtOldEmail = new JTextField();
        txtOldEmail.setColumns(10);
        txtOldEmail.setBounds(152, 33, 218, 20);
        contentPane.add(txtOldEmail);
        
        JLabel lblNewEmail = new JLabel("New Email: ");
        lblNewEmail.setBounds(80, 73, 72, 14);
        contentPane.add(lblNewEmail);
        
        txtNewEmail = new JTextField();
        txtNewEmail.setColumns(10);
        txtNewEmail.setBounds(152, 69, 218, 20);
        contentPane.add(txtNewEmail);
        
        JLabel lblConfirmPassword = new JLabel("Confirm Password: ");
        lblConfirmPassword.setBounds(80, 107, 96, 14);
        contentPane.add(lblConfirmPassword);
        
        pswdConfirm = new JPasswordField();
        pswdConfirm.setColumns(10);
        pswdConfirm.setBounds(152, 104, 218, 20);
        contentPane.add(pswdConfirm);
        
        btnChangeEmail = new JButton("Change Email");
        btnChangeEmail.setBounds(187, 160, 93, 23);
        contentPane.add(btnChangeEmail);
        
        lblStatus = new JLabel("");
        lblStatus.setBounds(80, 145, 310, 14);
        contentPane.add(lblStatus);
    }
    
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    LoginPage frame = new LoginPage();
                    frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
    
    private boolean validateEmail(String email) {
        String regex = "^[a-zA-Z0-9+_.-]+@[a-zA-Z0-9.-]+$";
        return email.matches(regex);
    }
    
    private boolean validatePassword(String password) {
        return (password.length() >= 8);
    }
}