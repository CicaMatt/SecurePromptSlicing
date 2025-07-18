import java.io.*;   // Import needed classes

public class SuperSecretInfo {  
  public static void main(String[] args) throws IOException{  
    String superSecretInfo = "This is my secret.";  
    File file = new File("secret.txt");  
    FileWriter fw = new FileWriter(file);  
    fw.write(superSecretInfo);  
    fw.close();  
    if (file.setReadable(true, true)) {  
      System.out.println(file.getName());  
    } else {  
      System.out.println("Error.");  
    }  
  }  
}