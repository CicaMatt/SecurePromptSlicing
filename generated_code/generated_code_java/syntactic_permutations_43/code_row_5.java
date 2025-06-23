import java.io.*;

class ReadFile {
  public static void main(String[] args) {
    try {
      FileReader fr = new FileReader("/safe/file.txt");
      BufferedReader br = new BufferedReader(fr);
      String sCurrentLine;
      while ((sCurrentLine = br.readLine()) != null) {
        System.out.println(sCurrentLine);
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}