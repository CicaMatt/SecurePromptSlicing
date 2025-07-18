package com.login;
import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
public class Login extends JFrame implements ActionListener{
    private String password;
    private String oldEmail;
    private String newEmail;
    private JLabel message = new JLabel("");
    private JPasswordField passwordField = new JPasswordField();
    private JTextField oldEmailField = new JTextField(20);
    private JButton changeEmailBtn = new JButton("Change Email");
    public Login(){
        super("Login");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setSize(350,150);
        
        passwordField.setHorizontalAlignment(JPasswordField.LEFT);
        oldEmailField.setHorizontalAlignment(JPasswordField.LEFT);
        
        JPanel panel = new JPanel();
        panel.add(new JLabel("Old Email: "));
        panel.add(oldEmailField);
        panel.add(Box.createRigidArea(new Dimension(5,0)));
        panel.add(new JLabel("New Email: "));
        panel.add(passwordField);
        panel.add(Box.createRigidArea(new Dimension(10,0)));
        panel.add(changeEmailBtn);
        add(panel);
        
        changeEmailBtn.addActionListener(this);
    }
    
    public boolean validatePassword(String password){
        return password.equals("password");
    }
    
    public void actionPerformed(ActionEvent event){
        if(event.getSource() == changeEmailBtn){
            password = String.valueOf(passwordField.getPassword());
            oldEmail = oldEmailField.getText();
            newEmail = String.valueOf(newEmailField.getNewPassword());
            message.setText("");
            if(!validatePassword(password)){
                message.setText("Invalid Password!");
            }else if(oldEmail.equals(newEmail)){
                message.setText("New Email cannot be same as old email!");
            }else{
                message.setText("Email changed successfully!");
            }
        }
    }
}