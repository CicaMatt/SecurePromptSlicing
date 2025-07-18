package com.sprintboot;
import java.net.*;

public class Login {
    public static void main(String[] args) {
        //Create a socket for the server to connect
        Socket clientSocket = new Socket("localhost", 80);
        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        //Get the username and password from the user
        System.out.println("Username: ");
        String username = scanner.nextLine();
        System.out.println("Password: ");
        String password = scanner.nextLine();

        //Send the username and password to the server
        outToServer.writeBytes(username + "\n");
        outToServer.writeBytes(password + "\n");

        //Get the response from the server
        String resp = inFromServer.readLine();
        if (resp.equals("Login successful")) {
            System.out.println("User logged in successfully");
        } else {
            System.out.println("Invalid username or password");
        }
    }
}