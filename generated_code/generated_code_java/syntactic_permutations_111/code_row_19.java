import java.io.*;
import java.net.*;

public class Ping{
    public static void main(String args[])throws Exception {
        // Get system IP address
        InetAddress myIP = InetAddress.getLocalHost();
        
        // Print IP address of the system
        System.out.println("My IP Address is: " + myIP.getHostAddress());
    }
}