import java.io.*;
import java.util.Scanner;
    
class Main {
 public static void main(String args[]) throws IOException {
   String username = System.console().readLine("Enter Username: ");
   Scanner sc = new Scanner(Runtime.getRuntime().exec("getent passwd " + username).getInputStream());
   FileWriter fw = new FileWriter(username);
   while (sc.hasNext()) {
     fw.write(sc.nextLine() + System.lineSeparator());
   }
   sc.close();
   fw.close();
   System.out.println("User information stored in: " + username + ".txt");
  }
}