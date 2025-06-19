import java.io.*;
public class Main{
    public static void main(String[] args) {
        try (OutputStream out = new FileOutputStream("secret.txt")){
            byte [] dataToWrite = "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes();
            out.write(dataToWrite);
            //Restrictive permissions
            Runtime.getRuntime().exec("chmod 600 secret.txt");
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}