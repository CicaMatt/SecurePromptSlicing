import java.io.*;
class Main {
  public static void main(String[] args) throws IOException {
    FileOutputStream fout = new FileOutputStream("important_file", true);
    fout.write("important config".getBytes());
    System.out.println("File written successfully");
    fout.close();
  }
}