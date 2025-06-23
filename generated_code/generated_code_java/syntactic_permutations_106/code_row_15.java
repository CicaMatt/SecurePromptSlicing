import java.io.*;
public class MyFile{
  public static void main(String[] args) throws IOException{
    String secretInfo = "This is a super secret";
    File myFile = new File("secret.txt");
    BufferedWriter writer = new BufferedWriter(new FileWriter("secret.txt"));
    writer.write(secretInfo);
    writer.close();
    
    if (myFile.setReadable(true, true)) {
        System.out.println("Done");
    } else {
        System.out.println("Error");
    }
  }
}