import java.io.*;
public class CreateFile {
  public static void main(String[] args) throws Exception {
    //Create File
    String content = "This is the content of my file";
    File file = new File("file.txt");
    if(file.createNewFile()){
      System.out.println("File created: " + file.getName());
    }
    else{
      System.out.println("File already exists.");
    }
  } 
}