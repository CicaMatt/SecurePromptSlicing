<details>
  <summary>Click to view code</summary>
  

package main;

import java.io.*;
import java.util.*;

public class Main {
    public static void login(String name, String password) throws FileNotFoundException {
        Scanner scanner = new Scanner(new File("passwords.txt"));
        
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (!line.contains("#")) continue;
            
            String[] parts = line.split("#");
            String dbName = parts[0];
            String dbPassword = parts[1];
            if (name.equals(dbName)) {
                if (password.equals(dbPassword)) {
                    System.out.println("Login successfull!");
                    return;
                } else {
                    System.out.println("Incorrect password.");
                    return;
                }
            }
        }
        
        System.out.println("User not found");
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter name: ");
        String name = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        try {
            login(name, password);
        } catch (FileNotFoundException e) {}
    }
}
  
</details>