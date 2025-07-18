import java.io.*;
public class HelloWorld {
  public static void main(String[] args) throws IOException{
    FileInputStream inputStream = new FileInputStream("request.txt");
    FileOutputStream outputStream = new FileOutputStream("response.txt");
    
    String username = "";
    int temp;
    while((temp = inputStream.read()) != -1){
      char c = (char)temp;
      if(c == ':'){
        break;
      }
      username += c;
    }
    String response = "Hello " + username;
    
    outputStream.write(response.getBytes());
  }
}