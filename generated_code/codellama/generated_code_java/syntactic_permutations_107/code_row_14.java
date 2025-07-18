import java.io.*;
public class Permissions {
  public static void main(String[] args) throws Exception{
    String output = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    File file = new File("secret.txt");
    if(!file.exists()){
      file.createNewFile();
    }
    BufferedWriter writer = new BufferedWriter(new FileWriter(file));
    writer.write(output);
    writer.close();
    Process process = Runtime.getRuntime().exec("chmod 700 secret.txt");
    process.waitFor();
    System.out.println("Permissions for 'secret.txt' file: ");
    process = Runtime.getRuntime().exec("ls -l secret.txt");
    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
    String line;
    while ((line = reader.readLine()) != null) {
      System.out.println(line);
    }
  }
}