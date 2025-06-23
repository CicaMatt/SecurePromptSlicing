import java.util.*;
	import javax.swing.*;
	import java.awt.event.ActionListener;
	import java.awt.event.ActionEvent;
	import javax.swing.JOptionPane;
	
	public class Login {
	private JTextField textField;
	private JPasswordField passwordField;
	private JLabel emailAddress, newEmailAddress;
	private JButton btnUpdate, btnSubmit; 
	private JPanel panel;
	private JFrame frame;
	private String oldEmail, newEmail, confirmPassowrd;
	private Boolean loggedIn;
	
	public Login(){
		loggedIn = false;
		oldEmail = "";
		newEmail = "";
		confirmPassword = "";
	}
	
	public void init() {
		frame = new JFrame("Login");
		panel = new JPanel();
		panel.setLayout(null);
		
		emailAddress = new JLabel("Email Address: ");
		emailAddress.setBounds(10, 20, 80, 25);
		panel.add(emailAddress);
		
		textField = new JTextField();
		textField.setBounds(100, 20, 160, 25);
		panel.add(textField);
		
		passwordField = new JPasswordField();
		passwordField.setBounds(100, 50, 160, 25);
		panel.add(passwordField);
		
		btnSubmit = new JButton("Login");
		btnSubmit.setBounds(10, 80, 80, 25);
		btnSubmit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try{
					String email = textField.getText();
					char[] pass = passwordField.getPassword();
					
					if((email != null && !email.isEmpty()) && (pass != null && pass.length > 0)) {
						//check if the user can login
						loggedIn = false;
					}
				}catch(Exception ex){
					JOptionPane.showMessageDialog(null, "Error logging in.", "Login", JOptionPane.ERROR_MESSAGE);
				}
			}
		});
		panel.add(btnSubmit);
		
		newEmailAddress = new JLabel("New Email Address: ");
		newEmailAddress.setBounds(10, 250, 160, 25);
		panel.add(newEmailAddress);
		
		JTextField newTextFiled = new JTextField();
		newTextFiled.setBounds(180, 250, 160, 25);
		panel.add(newTextFiled);
		
		btnUpdate = new JButton("Update");
		btnUpdate.setBounds(10, 300, 80, 25);
		btnUpdate.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try{
					String newEmail = textField.getText();
					char[] confirmPassowrd = passwordField.getPassword();
					
					if((newEmail != null && !newEmail.isEmpty()) && (confirmPassowrd != null && confirmPassowrd.length > 0)) {
						//check if the user can login
						loggedIn = false;
					}
				}catch(Exception ex){
					JOptionPane.showMessageDialog(null, "Error updating email.", "Update", JOptionPane.ERROR_MESSAGE);
				}
			}
		});
		panel.add(btnUpdate);
		
		frame.getContentPane().add(panel);
		frame.setSize(350, 400);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
	
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				Login login = new Login();
				login.init();
			}
		});
	}
}