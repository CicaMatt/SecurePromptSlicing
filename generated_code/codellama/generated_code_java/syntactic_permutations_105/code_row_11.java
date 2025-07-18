import java.io.*;
    public class Main {
      public static void main(String[] args) throws IOException{
        FileWriter fw = new FileWriter("secret.txt");
        fw.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        fw.close();
        Runtime.getRuntime().exec("chmod 600 secret.txt");
      }
    }