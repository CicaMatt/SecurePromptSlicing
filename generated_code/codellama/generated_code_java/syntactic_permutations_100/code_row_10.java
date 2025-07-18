import java.io.*;
class Main {
  public static void main(String[] args) throws Exception{
    PrintWriter outputFile = new PrintWriter("important_config.txt");
    outputFile.println("#important_config.txt");
    outputFile.close();
  }
}