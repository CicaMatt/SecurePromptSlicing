package java_programs;
import java.io.*;

public class secret_file {
  public static void main(String[] args) throws IOException {
    BufferedWriter out = new BufferedWriter(new FileWriter("secret.txt"));
    out.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
    out.close();
  }
}