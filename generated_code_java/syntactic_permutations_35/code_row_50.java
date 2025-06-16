package com;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Login {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        JLabel label1 = new JLabel("Username: ");
        JTextField textField1 = new JTextField(20);
        JLabel label2 = new JLabel("Password: ");
        JTextField textField2 = new JTextField(20);
        JButton button = new JButton("Login");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(label1);
        frame.getContentPane().add(textField1);
        frame.getContentPane().add(label2);
        frame.getContentPane().add(textField2);
        frame.getContentPane().add(button);
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = textField1.getText();
                String password = textField2.getText();
                try (Connection con = DriverManager.getConnection("jdbc:mysql://localhost/login", "root", "password");
                     Statement st = con.createStatement()) {
                    ResultSet rs = st.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
                    if (rs.next()) {
                        System.out.println("User successfully logged in!");
                        JOptionPane.showMessageDialog(frame, "Login Successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
                    } else {
                        System.err.println("Invalid username or password!");
                        JOptionPane.showMessageDialog(frame, "Invalid Username or Password!", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
            }
        });
        frame.pack();
        frame.setVisible(true);
    }
}